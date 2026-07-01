#include "redirect.h"
#include "redirect_priv.h"

t_error	redirect_stack_push(t_redir_stack *stack, t_redir_frame *frame)
{
	t_error	err;

	if (!vector_push(stack, frame))
	{
		err = error_sys();
		(void)redirect_restore_frame(frame);
		return (err);
	}
	return (error(ERR_NO));
}

t_error	redirect_stack_pop(t_redir_stack *stack, t_redir_frame *out_frame)
{
	if (!vector_pop(stack, out_frame))
		return (error(ERR_INCOHERENT_STATE));
	return (error(ERR_NO));
}

t_error	redirect_frame_push(t_redir_frame *frame, t_redir_backup *backup)
{
	t_error			err;

	if (frame == NULL)
		return (error(ERR_NO));
	if (!vector_push(frame, backup))
	{
		err = error_sys();
		redirect_restore_fds(backup);
		return (err);
	}
	return (error(ERR_NO));
}

// only last error is returned because we want to try to, anyway, revert as many fd as possible
t_error	redirect_restore_frame(t_redir_frame *frame)
{
	t_redir_backup	*backup;
	size_t			i;
	t_error			err;

	if (frame->len == 0)
		return (redirect_frame_free(frame), error(ERR_NO));
	i = 0;
	while (i < frame->len)
	{
		backup = &((t_redir_backup *)frame->data)[frame->len - 1 - i];
		err = redirect_restore_fds(backup);
		i++;
	}
	redirect_frame_free(frame);
	return (err);
}
