#include "redirector_priv.h"
#include "params.h"
#include "posix_helpers.h"
#include <limits.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

static inline t_error	redirect_print_and_qualify(
							t_error err,
							bool requalify_libc_errors,
							const char *message)
{
	if (err.type == ERR_NO || err.type == ERR_INTERRUPTED)
		return (err);
	err = error_print(err, REDIRECTOR_MODULE_NAME,
			message, NULL, NULL);
	if (err.type == ERR_INTERNAL || err.type == ERR_INVALID_USAGE)
		return (err);
	if (requalify_libc_errors == true && err.type == ERR_LIBC)
		err.type = ERR_REDIRECTION;
	return (err);
}

// @ret ERR_LIBC
static inline t_error	redirect_dir_is_writable(const t_string *dir, bool *out)
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

// @ret ERR_REDIRECTION / ERR_LIBC
static inline t_error	redirect_build_heredoc_fallback_path(t_string *out)
{
	bool	is_writable;
	t_error	err;

	if (!string_init(out, 0, "/tmp/", -1))
		return (error_sys());
	err = redirect_dir_is_writable(out, &is_writable);
	if (err.type)
		return (string_free(out), err);
	else if (is_writable == false)
		return (string_free(out), error(ERR_REDIRECTION));
	if (!string_append_n(out, "-heredoc-", -1))
		return (err = error_sys(), string_free(out), err);
	return (err);
}

// @ret ERR_REDIRECTION / ERR_INTERNAL / ERR_LIBC
static inline t_error	redirect_build_heredoc_base_path(t_string *out)
{
	bool		is_writable;
	t_error		err;

	err = params_get_from_const("TMPDIR", out);
	if (err.type == ERR_VAR_NOT_FOUND)
		return (redirect_build_heredoc_fallback_path(out));
	else if (err.type)
		return (err);
	else if (out->len == 0)
		return (string_free(out), redirect_build_heredoc_fallback_path(out));
	else if (out->data[out->len - 1] != '/' && !string_append_n(out, "/", 1))
		return (err = error_sys(), string_free(out), err);
	err = redirect_dir_is_writable(out, &is_writable);
	if (err.type)
		return (string_free(out), err);
	else if (is_writable == false)
		return (string_free(out), redirect_build_heredoc_fallback_path(out));
	if (!string_append_n(out, "-heredoc-", -1))
		return (err = error_sys(), string_free(out), err);
	return (err);
}

// @ret ERR_REDIRECTION / ERR_INTERRUPTED / ERR_INTERNAL / ERR_LIBC
t_error	redirect_open_heredoc(t_redirector *redirector, t_string *path, int *fd)
{
	size_t	initial_len;
	int		oflag;
	t_error	err;

	err = redirect_build_heredoc_base_path(path);
	if (err.type)
		return (err);
	initial_len = path->len;
	oflag = O_WRONLY | O_CREAT | O_EXCL;
	while (redirector->heredoc_id <= INT_MAX)
	{
		path->len = initial_len;
		if (!string_append_format(path, "%i", (int)redirector->heredoc_id))
			return (err = error_sys(), string_free(path), err);
		err = posix_open_with_mode(path->data, oflag, S_IRUSR | S_IWUSR, fd);
		if (err.type == ERR_NO)
			return (redirector->heredoc_id++, err);
		if (err.type != ERR_LIBC || err.saved_errno != EEXIST)
			break ;
		redirector->heredoc_id++;
	}
	string_free(path);
	if (redirector->heredoc_id > INT_MAX)
		return (error(ERR_REDIRECTION));
	return (redirect_print_and_qualify(err, true, "heredoc creation failed"));
}

t_error	redirect_get_heredoc_path(
			t_redirector *redirector,
			const t_string *body,
			char **out_path)
{
	int			fd;
	t_string	path;
	t_error		err;
	t_error		close_err;

	err = redirect_open_heredoc(redirector, &path, &fd);
	if (err.type)
		return (redirect_print_and_qualify(err, false,
					"unable to create heredoc file"));
	err = posix_write(fd, body->data, body->len);
	if (err.type)
		err = redirect_print_and_qualify(err, true,
					"unable to write to heredoc file");
	close_err = posix_close_if_open(fd);
	if (close_err.type)
		err = error_priorize(err, redirect_print_and_qualify(close_err, false,
					"unable to close heredoc file"));
	if (err.type && unlink(path.data) != 0)
		(void)error_print(error_sys(), REDIRECTOR_MODULE_NAME, "unable to "
			"unlink heredoc file", NULL, "'%s'", path.data);
	if (err.type)
		return (string_free(&path), err);
	*out_path = path.data;
	return (err);
}
