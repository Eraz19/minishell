#include "redirect_priv.h"
#include "posix_helpers.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

static inline t_error	redirect_location_failed(
							t_ast_redirection *redir,
							t_string *clean,
							t_error err)
{
	error_print(err, REDIRECT_MODULE_NAME,
		"io_location is not a valid file descriptor and path can't be opened",
		NULL, "'%s' expanded from '%s': redirection failed",
		clean->data, redir->location->value.data);
	err = error(ERR_REDIRECTION_FAILED);
	err.printed = true;
	return (err);	
}

static inline t_error	redirect_convert_location(
							t_ast_redirection *redir,
							t_redir_frame *frame)
{
	t_redir_backup	backup;
	t_string		clean;
	int				oflag;
	mode_t			mode;
	t_error			err;

	if (!string_init(&clean, 0, redir->expanded_location.data + 1,
		(long)redir->expanded_location.len - 2))
		return (error_sys());
	if (redirect_parse_fd(clean.data, &redir->fd))
		return (string_free(&clean), error(ERR_NO));
	oflag =  O_RDWR | O_CREAT | O_APPEND;
	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	err = posix_open_with_mode(clean.data, oflag, mode, &redir->fd);
	if (err.type)
		err = redirect_location_failed(redir, &clean, err);
	string_free(&clean);
	if (err.type)
		return (err);
	backup.backup_fd = -1;
	backup.fd = redir->fd;
	err = redirect_frame_push(frame, &backup);
	return (err);
}

t_error	redirect_normalize_fd(t_ast_redirection *redir, t_redir_frame *frame)
{
	t_ast_redir_op	operation;

	if (redir->is_location)
		return (redirect_convert_location(redir, frame));
	if (redir->fd >= 0)
		return error(ERR_NO);
	operation = redir->operation;
	if (operation == AST_REDIR_READ
		|| operation == AST_REDIR_HEREDOC
		|| operation == AST_REDIR_DUP_READ
		|| operation == AST_REDIR_READ_WRITE)
		redir->fd = STDIN_FILENO;
	else
		redir->fd = STDOUT_FILENO;
	return error(ERR_NO);
}
