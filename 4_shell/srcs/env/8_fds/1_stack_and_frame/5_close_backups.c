#include "error.h"
#include "redirect_stack.h"
#include "posix_helpers.h"
#include "fd_tracker.h"

static inline void	redirect_stack_close_frame_backups(
						const t_redir_frame *frame,
						t_fd_tracker *tracker)
{
	t_redir_backup	*backup;
	size_t			i;
	t_error			err;

	i = 0;
	while (i < frame->len)
	{
		err = redirect_frame_get_backup(frame, i, &backup);
		if (err.type)
			break ;
		if (backup->backup_fd >= 0)
		{
			err = posix_close_if_open(backup->backup_fd);
			if (err.type == ERR_NO)
			{
				fd_tracker_unlock(tracker, backup->backup_fd);
				backup->backup_fd = -1;
			}
		}
		i++;
	}
}

void	redirect_stack_close_backups(
			const t_redir_stack *redir_stack,
			t_fd_tracker *tracker)
{
	t_redir_frame	*frame;
	size_t			i;
	t_error			err;

	i = 0;
	while (i < redir_stack->len)
	{
		err = redirect_stack_get_frame(redir_stack, i, &frame);
		if (err.type)
			break ;
		redirect_stack_close_frame_backups(frame, tracker);
		i++;
	}
	tracker->next_available = TRACKER_MIN_FD_SHELL;
}
