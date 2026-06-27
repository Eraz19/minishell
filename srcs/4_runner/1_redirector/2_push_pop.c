#include "redirect_priv.h"

t_error	redirect_push(t_redir_stack *stack, t_redir_frame *frame)
{
	if (!vector_push(stack, frame))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	redirect_pop(t_redir_stack *stack)
{
	t_redir_frame	frame;

	if (!vector_pop(stack, &frame))
		return (error_sys());
	redirect_frame_free(&frame);
	return (error(ERR_NO));
}
