#include "fd.h"
#include "redirect_stack.h"
#include "fd_tracker.h"

void	fd_init(t_fd_manager *fd_manager)
{
	redirect_stack_init(&fd_manager->stack);
	fd_tracker_init(&fd_manager->tracker, &fd_manager->stack);
	fd_manager->max_frame_count = 0;
	fd_manager->heredoc_id = 0;
}

void	fd_init_subshell(t_fd_manager *fd_manager)
{
	(void)fd_clear(fd_manager, false);
}

t_error	fd_clear(t_fd_manager *fd_manager, bool restore_redirections)
{
	if (restore_redirections == true)
		return (fd_restore_stack());
	redirect_stack_close_backups(&fd_manager->stack, &fd_manager->tracker);
	redirect_stack_clear(&fd_manager->stack);
	return (error(ERR_NO));
}

void	fd_free(t_fd_manager *fd_manager)
{
	(void)fd_restore_stack();
	redirect_stack_free(&fd_manager->stack, fd_manager->max_frame_count);
	fd_tracker_free(&fd_manager->tracker);
	fd_manager->max_frame_count = 0;
	fd_manager->heredoc_id = 0;
}
