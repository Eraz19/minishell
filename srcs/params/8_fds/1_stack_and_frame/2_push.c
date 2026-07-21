#include "redirect_stack.h"

t_error	redirect_stack_push(t_redir_stack *stack, t_redir_frame *frame)
{
	if (!vector_push(stack, frame))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	redirect_frame_push(t_redir_stack *stack, t_redir_backup *backup)
{
	t_redir_frame	*frame;
	t_error			err;

	err = redirect_stack_get_current_frame(stack, &frame);
	if (err.type)
		return (err);
	if (!vector_push(frame, backup))
		return (error_sys());
	return (error(ERR_NO));
}
