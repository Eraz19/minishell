#include "redirector_priv.h"
#include "posix_helpers.h"
#include "fd_manager.h"
#include <unistd.h>
#include <errno.h>

// @ret ERR_REDIRECTION / ERR_INTERRUPTED / ERR_INTERNAL / ERR_LIBC
static inline t_error	redirect_redirect(
							t_redirector *redirector,
							t_redir *redirection,
							bool *applied)
{
	int		opened_fd;
	t_error	err;

	err = redirect_open(redirector, redirection, &opened_fd);
	if (err.type)
		return (err);
	else if (opened_fd == redirection->fd)
		return (*applied = true, err);
	err = posix_dup2(opened_fd, redirection->fd);
	if (err.type)
	{
		(void)posix_close_if_open(opened_fd);
		if (err.type == ERR_LIBC)
			err.type = ERR_REDIRECTION;
		return (err);
	}
	*applied = true;
	return (posix_close_if_open(opened_fd));
}

// @ret ERR_REDIRECTION / ERR_INTERRUPTED
static inline t_error	redirect_dup(t_redir *redir, bool *applied)
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
			err = error_print(error(ERR_REDIRECTION),
				REDIRECTOR_MODULE_NAME, "file descriptor is not valid", NULL,
				"%i expanded from '%s'", rhs_fd, redir->word->value.data);
	}
	if (err.type == ERR_LIBC)
		err.type = ERR_REDIRECTION;
	if (err.type == ERR_NO)
		*applied = true;
	return (err);
}

static inline t_error	redirect_handle_failure(
							t_redir *redir,
							t_redirector *redirector,
							t_error err)
{
	t_error	restore_err;

	redir_free(redir);
	restore_err = fd_restore_last_backup(redirector);
	if (restore_err.type)
		return (restore_err);
	return (err);
}

t_error	redirect_apply(
			const t_ast_redirection *redirection,
			t_redirector *redirector,
			bool permanent,
			int *exit_status)
{
	t_redir			redir;
	t_ast_redir_op	operation;
	bool			applied;
	t_error			err;

	applied = false;
	redir_init(&redir, redirection);
	err = redirect_expand(&redir, exit_status);
	if (err.type == ERR_NO && redir.is_location == true)
		err = redirect_resolve_location(&redir);
	if (err.type == ERR_NO)
		err = redirect_prepare(&redir, redirector, permanent);
	if (err.type)
		return (redir_free(&redir), err);
	operation = redir.operation;
	if (operation == AST_REDIR_DUP_READ || operation == AST_REDIR_DUP_WRITE)
		err = redirect_dup(&redir, &applied);
	else
		err = redirect_redirect(redirector, &redir, &applied);
	if (err.type && permanent == false)
		return (redirect_handle_failure(&redir, redirector, err));
	else if (permanent == true && applied == true)
		fd_save_perm(redirector, redir.fd);
	return (redir_free(&redir), err);
}
