#include "redirector.h"
#include "redirector_priv.h"
#include "redirect_stack.h"
#include "fd_manager.h"
#include <errno.h>
#include <unistd.h>

// @ret ERR_LIBC
static inline t_error	redirect_use_new_frame(t_redirector *redirector)
{
	t_redir_frame	frame;
	t_redir_frame	*frame_ptr;
	t_error			err;

	if (redirector->stack.len < redirector->max_frame_count)
	{
		frame_ptr = ((t_redir_frame *)redirector->stack.data);
		frame_ptr += redirector->stack.len;
		frame_ptr->len = 0;
		redirector->stack.len++;
		return (error(ERR_NO));
	}
	redirect_frame_init(&frame);
	err = redirect_stack_push(&redirector->stack, &frame);
	if (err.type == ERR_NO)
		redirector->max_frame_count++;
	return (err);
}

t_error	redirect_commit(
			t_redirector *redirector,
			const t_ast_redir_list *redirections,
			int *exit_status)
{
	size_t					i;
	const t_ast_redirection	*redirection;
	t_error					err;

	err = error(ERR_NO);
	i = 0;
	while (i < redirections->len)
	{
		redirection = &((t_ast_redirection *)redirections->data)[i];
		err = redirect_apply(redirection, redirector, true, exit_status);
		if (err.type)
			break ;
		i++;
	}
	return (err);
}

t_error	redirect_start(
			t_redirector *redirector,
			const t_ast_redir_list *redirections,
			int *exit_status)
{
	size_t					i;
	const t_ast_redirection	*redirection;
	t_error					err;
	t_error					restore_err;

	err = redirect_use_new_frame(redirector);
	if (err.type)
		return (err);
	i = 0;
	while (i < redirections->len)
	{
		redirection = &((t_ast_redirection *)redirections->data)[i];
		err = redirect_apply(redirection, redirector, false, exit_status);
		if (err.type)
		{
			restore_err = fd_restore_last_frame(redirector);
			if (restore_err.type)
				err = restore_err;
			break ;
		}
		i++;
	}
	return (err);
}

t_error	redirect_stop(t_redirector *redirector)
{
	return (fd_restore_last_frame(redirector));
}
