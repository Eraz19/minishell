#include "posix_helpers.h"
#include "fd_tracker.h"
#include "redirect_stack.h"
#include "params.h"
#include "fd.h"

// @ret ERR_NO / ERR_LIBC
static inline t_error	fd_restore_fds(
							t_fd_tracker *fd_tracker,
							t_redir_backup *backup)
{
	t_error	err;

	if (backup->backup_fd == -1)
	{
		err = posix_close_if_open(backup->fd);
		if (err.type == ERR_NO)
			fd_tracker_unlock(fd_tracker, backup->fd);
		return (err);
	}
	err = posix_dup2(backup->backup_fd, backup->fd);
	if (err.type)
		return (err);
	fd_tracker_unlock(fd_tracker, backup->fd);
	err = posix_close_if_open(backup->backup_fd);
	if (err.type == ERR_NO)
		fd_tracker_unlock(fd_tracker, backup->backup_fd);
	return (err);
}

// @ret ERR_NO / ERR_INTERNAL / ERR_LIBC
static inline t_error	fd_restore_frame(
							t_fd_tracker *fd_tracker,
							t_redir_frame *frame)
{
	t_redir_backup	*backup;
	t_error			err;

	err = error(ERR_NO);
	while (frame->len > 0)
	{
		err = redirect_frame_get_current_backup(frame, &backup);
		if (err.type)
			return (err);
		frame->len--;
		err = fd_restore_fds(fd_tracker, backup);
		if (err.type)
			return (err);
	}
	return (err);
}

// @ret ERR_NO / ERR_INTERNAL / ERR_LIBC
t_error	fd_restore_stack(void)
{
	t_fd_manager	*fd_manager;
	t_redir_frame	*frame;
	t_error			err;

	err = params_get_fd_manager(&fd_manager);
	if (err.type)
		return (err);
	while (fd_manager->stack.len > 0)
	{
		err = redirect_stack_get_current_frame(&fd_manager->stack, &frame);
		if (err.type)
			return (err);
		fd_manager->stack.len--;
		err = fd_restore_frame(&fd_manager->tracker, frame);
		if (err.type)
			return (err);
	}
	return (err);
}

// @ret ERR_NO / ERR_INTERNAL / ERR_LIBC
t_error	fd_restore_last_backup(void)
{
	t_fd_manager	*fd_manager;
	t_redir_frame	*frame;
	t_redir_backup	*backup;
	t_error			err;

	err = params_get_fd_manager(&fd_manager);
	if (err.type)
		return (err);
	err = redirect_stack_get_current_frame(&fd_manager->stack, &frame);
	if (err.type)
		return (err);
	err = redirect_frame_get_current_backup(frame, &backup);
	if (err.type)
		return (err);
	frame->len--;
	return (fd_restore_fds(&fd_manager->tracker, backup));
}

// @ret ERR_NO / ERR_INTERNAL / ERR_LIBC
t_error	fd_restore_last_frame(void)
{
	t_fd_manager	*fd_manager;
	t_redir_frame	*frame;
	t_error			err;

	err = params_get_fd_manager(&fd_manager);
	if (err.type)
		return (err);
	err = redirect_stack_get_current_frame(&fd_manager->stack, &frame);
	if (err.type)
		return (err);
	fd_manager->stack.len--;
	return (fd_restore_frame(&fd_manager->tracker, frame));
}
