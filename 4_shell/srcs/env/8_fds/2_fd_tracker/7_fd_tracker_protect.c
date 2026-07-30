#include "error.h"
#include "fd_tracker.h"
#include "fd_tracker_priv.h"
#include "redirect_stack.h"
#include "posix_helpers.h"

t_error	fd_tracker_protect(t_fd_tracker *tracker, int fd)
{
	int				new_backup_fd;
	size_t			frame_i;
	size_t			backup_i;
	t_redir_backup	*backup;
	t_error			err;

	if (fd_tracker_fd_is_used_by_shell(tracker, fd) == false)
		return (error(ERR_NO));
	frame_i = tracker->data[fd].frame_index;
	backup_i = tracker->data[fd].backup_index;
	err = redirect_stack_get_backup(tracker->stack, frame_i, backup_i, &backup);
	if (err.type)
		return (err);
	err = fd_tracker_backup_priv(tracker, fd, &new_backup_fd);
	if (err.type == ERR_NO)
		err = fd_tracker_grow(tracker, (size_t)new_backup_fd + 1);
	if (err.type == ERR_NO)
		err = posix_close_if_open(fd);
	if (err.type)
		return ((void)posix_close_if_open(new_backup_fd), err);
	backup->backup_fd = new_backup_fd;
	tracker->data[new_backup_fd].is_used_by_shell = true;
	tracker->data[new_backup_fd].frame_index = frame_i;
	tracker->data[new_backup_fd].backup_index = backup_i;
	return (fd_tracker_unlock(tracker, fd), err);
}
