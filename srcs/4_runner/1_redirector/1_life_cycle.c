#include "redirect.h"

void	redirect_init(t_redir_stack *stack)
{
	(void)vector_init(stack, sizeof(t_redir_frame), 0);
}

void	redirect_free(t_redir_stack *stack)
{
	vector_free(stack, NULL);
}

void	redirect_frame_init(t_redir_frame *frame)
{
	vector_init(&frame->fds, sizeof(int), 0);
	vector_init(&frame->backup_fds, sizeof(int), 0);
}

void	redirect_frame_free(void *frame)
{
	t_redir_frame	*frame_ptr;

	frame_ptr = (t_redir_frame *)frame;
	vector_free(&frame_ptr->fds, NULL);
	vector_free(&frame_ptr->backup_fds, NULL);
}
