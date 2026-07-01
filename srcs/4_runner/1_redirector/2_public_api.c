#include "redirect.h"
#include "redirect_priv.h"
#include <errno.h>

void	redirect_init(t_redir_stack *stack)
{
	(void)vector_init(stack, sizeof(t_redir_frame), 0);
}

t_error	redirect_commit(t_ast_redir_list *redirections)
{
	size_t				i;
	t_ast_redirection	*redir;
	t_error				err;

	if (redirections->len == 0)
		return (error(ERR_NO));
	i = 0;
	while (i < redirections->len)
	{
		redir = &((t_ast_redirection *)redirections->data)[i];
		err = redirect_apply(redir, NULL);
		if (err.type)
			return (err);
		i++;
	}
	return (err);
}

t_error	redirect_start(t_redir_stack *stack, t_ast_redir_list *redirections)
{
	size_t				i;
	t_ast_redirection	*redir;
	t_redir_frame		frame;
	t_error				err;

	redirect_frame_init(&frame);
	i = 0;
	while (i < redirections->len)
	{
		redir = &((t_ast_redirection *)redirections->data)[i];
		err = redirect_apply(redir, &frame);
		if (err.type)
			return ((void)redirect_restore_frame(&frame), err);
		i++;
	}
	return (redirect_stack_push(stack, &frame));
}

t_error	redirect_stop(t_redir_stack *stack)
{
	t_redir_frame	frame;
	t_error			err;

	err = redirect_stack_pop(stack, &frame);
	if (err.type)
		return (err);
	return (redirect_restore_frame(&frame));
}

void	redirect_free(t_redir_stack *stack)
{
	while (stack->len > 0)
		redirect_stop(stack);
	vector_free(stack, redirect_frame_free);
}
