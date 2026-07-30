#include "fd.h"
#include "env.h"
#include "posix_helpers.h"
#include <limits.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

// @ret ERR_NO / ERR_LIBC
static inline t_error	fd_dir_is_writable(const t_string *dir, bool *out)
{
	struct stat	st;

	*out = false;
	if (dir->data == NULL || dir->len == 0)
		return (error(ERR_NO));
	if (stat(dir->data, &st) < 0)
	{
		if (errno == EACCES || errno == ELOOP || errno == ENAMETOOLONG
			|| errno == ENOENT || errno == ENOTDIR || errno == EROFS)
			return (error(ERR_NO));
		return (error_sys());
	}
	if (S_ISDIR(st.st_mode) == false)
		return (error(ERR_NO));
	if (access(dir->data, W_OK | X_OK) == 0)
		return (*out = true, error(ERR_NO));
	else if (errno == EACCES || errno == ELOOP || errno == ENAMETOOLONG
		|| errno == ENOENT || errno == ENOTDIR || errno == EROFS)
		return (error(ERR_NO));
	return (error_sys());
}

// @ret ERR_NO / ERR_REDIRECTION / ERR_LIBC
static inline t_error	fd_build_heredoc_fallback_path(t_string *out)
{
	bool	is_writable;
	t_error	err;

	if (!string_init(out, 0, "/tmp/", -1))
		return (error_sys());
	err = fd_dir_is_writable(out, &is_writable);
	if (err.type)
		return (string_free(out), err);
	else if (is_writable == false)
		return (string_free(out), error(ERR_REDIRECTION));
	if (!string_append_n(out, "-heredoc-", -1))
		return (err = error_sys(), string_free(out), err);
	return (err);
}

// @ret ERR_NO / ERR_REDIRECTION / ERR_INTERNAL / ERR_LIBC
static inline t_error	fd_build_heredoc_base_path(t_string *out)
{
	bool		is_writable;
	t_error		err;

	err = env_get_from_const("TMPDIR", out);
	if (err.type == ERR_VAR_NOT_FOUND)
		return (fd_build_heredoc_fallback_path(out));
	else if (err.type)
		return (err);
	else if (out->len == 0)
		return (string_free(out), fd_build_heredoc_fallback_path(out));
	else if (out->data[out->len - 1] != '/' && !string_append_n(out, "/", 1))
		return (err = error_sys(), string_free(out), err);
	err = fd_dir_is_writable(out, &is_writable);
	if (err.type)
		return (string_free(out), err);
	else if (is_writable == false)
		return (string_free(out), fd_build_heredoc_fallback_path(out));
	if (!string_append_n(out, "-heredoc-", -1))
		return (err = error_sys(), string_free(out), err);
	return (err);
}

// @ret ERR_NO / ERR_REDIRECTION / ERR_INTERNAL / ERR_LIBC
static inline t_error	fd_open_heredoc_loop(
							t_fd_manager *fd_manager,
							t_string *path,
							int *fd)
{
	size_t	initial_len;
	int		oflag;
	t_error	err;

	initial_len = path->len;
	oflag = O_WRONLY | O_CREAT | O_EXCL;
	while (fd_manager->heredoc_id <= INT_MAX)
	{
		path->len = initial_len;
		if (!string_append_format(path, "%i", (int)fd_manager->heredoc_id))
			return (err = error_sys(), err);
		err = posix_open_with_mode(path->data, oflag, S_IRUSR | S_IWUSR, fd);
		if (err.type == ERR_INVALID_USAGE)
		{
			err = error_print(err, __func__, NULL, NULL);
			return (err.type = ERR_INTERNAL, err);
		}
		if (err.type == ERR_NO)
			return (fd_manager->heredoc_id++, err);
		if (err.type != ERR_LIBC || err.saved_errno != EEXIST)
			return (err);
		fd_manager->heredoc_id++;
	}
	err = error(ERR_REDIRECTION);
	return (error_print(err, "too much heredoc temp files", NULL, NULL));
}

// @ret ERR_NO / ERR_REDIRECTION / ERR_INTERNAL / ERR_LIBC
t_error	fd_open_heredoc(t_string *path, int *fd)
{
	t_fd_manager	*fd_manager;
	t_error			err;

	err = env_get_fd_manager(&fd_manager);
	if (err.type == ERR_NO)
		err = fd_build_heredoc_base_path(path);
	if (err.type)
		return (err);
	err = fd_open_heredoc_loop(fd_manager, path, fd);
	if (err.type)
		string_free(path);
	return (err);
}
