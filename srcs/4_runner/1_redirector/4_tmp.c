#include "ast_type.h"
#include "options.h"
#include "posix_helpers.h"
#include "redirect.h"
#include "redirect_priv.h"
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

// move to utils
t_error	is_a_regular_file(t_string *path, bool *out)
{
	if (path->len == 0)
		return (*out = false, error(ERR_NO));
	// TODO
	*out = false;
	return (error(ERR_NO));
}

int	redirect_get_oflag(
	t_ast_redirection *redirection,
	bool no_clobber_is_active)
{
	int				oflag;
	t_ast_redir_op	op;

	op = redirection->operation;
	oflag = 0;
	if (op == AST_REDIR_READ || op == AST_REDIR_HEREDOC)
		oflag = O_RDONLY;
	else if (op == AST_REDIR_WRITE || op == AST_REDIR_CLOBBER)
	{
		oflag = O_WRONLY | O_CREAT | O_TRUNC;
		if (op == AST_REDIR_WRITE && no_clobber_is_active)
			oflag |= O_EXCL;
	}
	else if (op == AST_REDIR_APPEND)
		oflag = O_WRONLY | O_CREAT | O_APPEND;
	else if (op == AST_REDIR_READ_WRITE)
		oflag = O_RDWR | O_CREAT;
	return (oflag);
}

static inline t_error	redirect_get_source_fd(
	t_ast_redirection *redirection,
	int *out)
{
	bool			no_clobber_is_active;
	int				oflag;
	bool			is_regular_file;
	t_ast_redir_op	op;
	t_error			err;

	err = option_is_active(OPT_NOCLOBBER, &no_clobber_is_active);
	if (err.type)
		return (err);
	oflag = redirect_get_oflag(redirection, no_clobber_is_active);
	err = posix_open(redirection->word->value.data, oflag, out);
	op = redirection->operation;
	if (err.type == ERR_LIBC && errno == EBADF
		&& (op == AST_REDIR_DUP_READ || op == AST_REDIR_DUP_WRITE))
	{	 
		err = error(ERR_REDIRECTION_FAILED);
		return (error_print(err, "redirector", "fd is not open", NULL, NULL));
	}
	else if (*out == -1 && op == AST_REDIR_WRITE && no_clobber_is_active)
	{
		if (errno == EEXIST)
		{
			err = is_a_regular_file(&redirection->word->value, &is_regular_file);
			if (err.type)
				return (err);
			else if (!is_regular_file)
			{
				// TODO: open as non-regular file (what does it mean ?!)
			}
		}
		err = error(ERR_REDIRECTION_FAILED);
		return (error_print(err, "redirector", "TODO", NULL, NULL));
		// Output redirection using the '>' format shall fail if the noclobber option is set (see the description of set -C) and the file named by the expansion of word exists and is either a regular file or a symbolic link that resolves to a regular file; it may also fail if the file is a symbolic link that does not resolve to an existing file. The check for existence, file creation, and open operations shall be performed atomically as is done by the open() function as defined in System Interfaces volume of POSIX.1-2024 when the O_CREAT and O_EXCL flags are set, except that if the file exists and is a symbolic link, the open operation need not fail with [EEXIST] unless the symbolic link resolves to an existing regular file
	}
	return (error(ERR_NO));
}

static inline t_error	redirect_push_to_frame(
	t_redir_frame *frame,
	int backup_fd,
	int new_fd)
{
	if (!vector_push(&frame->backup_fds, &backup_fd))
		return (error_sys());
	if (!vector_push(&frame->fds, &new_fd))
		return (error_sys());
	// TODO: restore fds on error
	return (error(ERR_NO));
}

t_error	redirect_apply(t_ast_redirection *redirection, t_redir_frame *frame)
{
	int		backup_fd;
	int		source_fd;
	int		new_fd;
	t_error	err;

	err = redirect_prepare(redirection, &backup_fd);
	if (err.type == ERR_NO)
		err = redirect_get_source_fd(redirection, &source_fd);
	if (err.type)
		return (err);
	new_fd = dup2(source_fd, redirection->fd);
	// TODO: check dup2 return value ?
	// TODO: check that file is open for input or output ?
	if (redirection->operation != AST_REDIR_DUP_READ
		&& redirection->operation != AST_REDIR_DUP_WRITE)
		close(source_fd);
	return (redirect_push_to_frame(frame, backup_fd, new_fd));
}
