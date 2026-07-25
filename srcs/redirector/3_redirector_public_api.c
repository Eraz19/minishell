#include "redirector.h"
#include "redirector_priv.h"
#include "fd.h"

t_error	redirect_commit(const t_ast_redir_list *redirections, int *exit_status)
{
	size_t					i;
	const t_ast_redirection	*redirection;
	t_error					err;

	err = error(ERR_NO);
	i = 0;
	while (i < redirections->len)
	{
		redirection = &((t_ast_redirection *)redirections->data)[i];
		err = redirect_apply(redirection, true, exit_status);
		if (err.type)
			break ;
		i++;
	}
	return (err);
}

t_error	redirect_start(const t_ast_redir_list *redirections, int *exit_status)
{
	size_t					i;
	const t_ast_redirection	*redirection;
	t_error					err;
	t_error					restore_err;

	err = fd_use_new_frame();
	if (err.type)
		return (err);
	i = 0;
	while (i < redirections->len)
	{
		redirection = &((t_ast_redirection *)redirections->data)[i];
		err = redirect_apply(redirection, false, exit_status);
		if (err.type)
		{
			restore_err = fd_restore_last_frame();
			if (restore_err.type)
				err = restore_err;
			break ;
		}
		i++;
	}
	return (err);
}

t_error	redirect_stop(void)
{
	return (fd_restore_last_frame());
}
