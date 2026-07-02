#include "redirector.h"
#include "fd_tracker.h"
#include "redirect_stack.h"
#include "fd_manager.h"

void	redirect_init(t_redirector *redirector)
{
	redirector->max_frame_count = 0;
	redirect_stack_init(&redirector->stack);
	fd_tracker_init(&redirector->tracker, &redirector->stack);
}

void	redirect_free(t_redirector *redirector)
{
	(void)fd_restore_stack(redirector);
	redirect_stack_free(&redirector->stack, redirector->max_frame_count);
	fd_tracker_free(&redirector->tracker);
	redirector->max_frame_count = 0;
}
