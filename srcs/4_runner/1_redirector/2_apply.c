#include "redirector_priv.h"
#include "posix_helpers.h"
#include "fd_manager.h"
#include <unistd.h>
#include <errno.h>

static inline t_error	redirect_redirect(t_ast_redirection *redirection)
{
	int		opened_fd;
	t_error	err;

	err = redirect_open(redirection, &opened_fd);
	if (err.type)
		return (err);
	else if (opened_fd == redirection->fd)
		return (err);
	err = posix_dup2(opened_fd, redirection->fd);
	if (err.type)
		return ((void)posix_close_if_open(opened_fd), err);
	return (posix_close_if_open(opened_fd));
}

static inline t_error	redirect_dup(t_ast_redirection *redir)
{
	int		rhs_fd;
	t_error	err;

	if (redir->expanded_word.len == 1 && redir->expanded_word.data[0] == '-')
		err = posix_close_if_open(redir->fd);
	else
	{
		(void)redirect_parse_fd(redir->expanded_word.data, &rhs_fd);
		err = posix_dup2(rhs_fd, redir->fd);
		if (err.type == ERR_LIBC && err.saved_errno == EBADF)
			err = error_print(error(ERR_POSIX_REDIRECTION),
				REDIRECTOR_MODULE_NAME, "file descriptor is not valid", NULL,
				"%i expanded from '%s'", rhs_fd, redir->word->value.data);
	}
	return (err);
}

static inline t_error	redirect_handle_failure(
							t_redirector *redirector,
							t_error err)
{
	t_error	restore_err;

	restore_err = fd_restore_last_backup(redirector);
	if (restore_err.type)
		return (restore_err);
	return (err);
}

t_error	redirect_apply(
			t_ast_redirection *redirection,
			t_redirector *redirector,
			bool permanent)
{
	t_ast_redir_op	operation;
	t_error			err;

	err = redirect_expand(redirection);
	if (err.type == ERR_NO)
		err = redirect_normalize_fd(redirection);
	if (err.type == ERR_NO)
		err = redirect_prepare(redirection, redirector, permanent);
	if (err.type)
		return (err);
	operation = redirection->operation;
	if (operation == AST_REDIR_DUP_READ || operation == AST_REDIR_DUP_WRITE)
		err = redirect_dup(redirection);
	else
		err = redirect_redirect(redirection);
	if (err.type && permanent == false)
		return (redirect_handle_failure(redirector, err));
	else if (err.type == ERR_NO && permanent == true)
		fd_save_perm(redirector, redirection->fd);
	return (err);
}
