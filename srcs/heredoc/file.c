#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include "limits.h"
#include "heredoc_.h"
#include "posix_helpers.h"

static inline bool	max_id_reached(t_heredoc *heredoc)
{
	t_error	err;
	int		errno_;
	int		file_id;

	err = heredoc->err;
	errno_ = err.saved_errno;
	file_id = heredoc->file_id;
	return (err.type == ERR_LIBC && errno_ == EEXIST && file_id == INT_MAX);
}

t_error	try_create_heredoc_file(t_heredoc *heredoc,t_string *path, int *fd)
{
	int	o_flag;

	heredoc->file_id++;
	o_flag = O_CREAT | O_EXCL | O_WRONLY;
	if (!string_append_format(path, "%i", (int)heredoc->file_id))
		return (heredoc->err = error_sys(), string_free(path), heredoc->err);
	heredoc->err = posix_open_with_mode(path->data, o_flag, 0600, fd);
	return (close(*fd), heredoc->err);
}

t_error	create_heredoc_file(t_heredoc *heredoc, t_string *path)
{
	int		fd;
	size_t	initial_len;

	fd = -1;
	initial_len = path->len;
	if (!string_init(path, 0, HEREDOC_TMP_PATH, sizeof(HEREDOC_TMP_PATH) - 1))
		return (heredoc->err = error_sys());
	while (heredoc->file_id < INT_MAX)
	{
		try_create_heredoc_file(heredoc, path, &fd);
		if (heredoc->err.type != ERR_LIBC || heredoc->err.saved_errno != EEXIST)
			break ;
		path->len = initial_len;
	}
	if (max_id_reached(heredoc))
		heredoc->err = error(ERR_HEREDOC_MAX_ID_REACHED);
	if (heredoc->err.type)
	{
		error_print(heredoc->err, "heredoc", "unable to create file",
			NULL, NULL);
		return (string_free(path), heredoc->err);
	}
	return (heredoc->err);
}
