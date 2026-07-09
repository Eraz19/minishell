#include "posix_helpers.h"
#include "fd_tracker.h"
#include "fd_tracker_priv.h"
#include "redirector_priv.h"
#include "redirect_stack.h"
#include <errno.h>
#include <limits.h>
#include <sys/stat.h>

static inline void	fd_tracker_update_next_available_fd(
						t_fd_tracker *tracker,
						int fd)
{
	while (fd_tracker_fd_is_used(tracker, fd))
		fd++;
	tracker->next_available = (size_t)fd;
}

// @ret ERR_REDIRECTION / ERR_LIBC
static inline t_error	fd_tracker_get_candidate(
							t_fd_tracker *tracker,
							int *out_candidate)
{
	int			candidate;
	struct stat	info;

	candidate = (int)tracker->next_available - 1;
	while (candidate < INT_MAX)
	{
		candidate++;
		if (fd_tracker_fd_is_used(tracker, candidate))
			continue ;
		if (fstat(candidate, &info) == 0)
			continue ;
		else if (errno == EBADF)
			break ;
		return (error_sys());
	}
	if (candidate == INT_MAX)
		return (redirect_print_error_all_fd_used());
	*out_candidate = candidate;
	return (error(ERR_NO));
}

t_error	fd_tracker_backup_priv(
			t_fd_tracker *tracker,
			int fd,
			int *out_backup_fd)
{
	int				backup_fd;
	struct stat		info;
	t_error			err;

	*out_backup_fd = -1;
	if (fd < 0)
		return (error(ERR_NO));
	if (fstat(fd, &info) < 0)
	{
		if (errno == EBADF)
			return (error(ERR_NO));
		return (error_sys());
	}
	err = fd_tracker_get_candidate(tracker, &backup_fd);
	if (err.type)
		return (err);
	err = posix_dup2(fd, backup_fd);
	if (err.saved_errno == EBADF)
		return (redirect_print_error_all_fd_used());
	else if (err.type)
		return ((void)posix_close_if_open(backup_fd), err);
	fd_tracker_update_next_available_fd(tracker, (int)backup_fd + 1);
	*out_backup_fd = backup_fd;
	return (err);
}

t_error	fd_tracker_backup(t_fd_tracker *tracker, int fd, int *out_backup_fd)
{
	int				backup_fd;
	t_tracked_fd	*tracked_fd;
	t_redir_frame	*frame;
	t_error			err;

	err = fd_tracker_backup_priv(tracker, fd, &backup_fd);
	if (err.type)
		return (err);
	else if (backup_fd < 0)
		return (*out_backup_fd = backup_fd, err);
	err = redirect_stack_get_current_frame(tracker->stack, &frame);
	if (err.type)
	{
		(void)posix_close_if_open(backup_fd);
		return (error_print(err, REDIRECTOR_MODULE_NAME,
			"unable to lock shell fd", NULL, NULL));
	}
	err = fd_tracker_grow(tracker, (size_t)backup_fd + 1);
	if (err.type)
		return ((void)posix_close_if_open(backup_fd), err);
	tracked_fd = &tracker->data[backup_fd];
	tracked_fd->is_used_by_shell = true;
	tracked_fd->frame_index = tracker->stack->len - 1;
	tracked_fd->backup_index = frame->len;
	return (*out_backup_fd = backup_fd, err);
}
