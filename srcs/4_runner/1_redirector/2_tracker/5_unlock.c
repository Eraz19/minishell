#include "fd_tracker.h"

void	fd_tracker_unlock(t_fd_tracker *tracker, int fd)
{
	if (fd < TRACKER_MIN_FD_SHELL || (size_t)fd >= tracker->cap)
		return ;
	else if (tracker->data[fd].user_count > 1)
	{
		tracker->data[fd].user_count--;
		return ;
	}
	else if (tracker->data[fd].is_used_by_shell
		|| tracker->data[fd].user_count == 1)
	{
		tracker->data[fd] = (t_tracked_fd){0};
	}
	if ((size_t)fd < tracker->next_available)
		tracker->next_available = (size_t)fd;
}
