#include "posix_helpers.h"
#include "fd_tracker.h"
#include "redirect_stack.h"
#include "redirector_type.h"
#include "fd_manager.h"

t_error	fd_restore_fds(t_redirector *redirector, t_redir_backup *backup)
{
	t_error	err;

	if (backup->backup_fd == -1)
	{
		err = posix_close_if_open(backup->fd);
		if (err.type == ERR_NO)
			fd_tracker_unlock(&redirector->tracker, backup->fd);
		return (err);
	}
	err = posix_dup2(backup->backup_fd, backup->fd);
	if (err.type)
		return (err);
	fd_tracker_unlock(&redirector->tracker, backup->fd);
	err = posix_close_if_open(backup->backup_fd);
	if (err.type == ERR_NO)
		fd_tracker_unlock(&redirector->tracker, backup->backup_fd);
	return (err);
}

t_error	fd_restore_frame(t_redirector *redirector, t_redir_frame *frame)
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
		err = fd_restore_fds(redirector, backup);
		if (err.type)
			return (err);
	}
	return (err);
}

t_error	fd_restore_stack(t_redirector *redirector)
{
	t_redir_frame	*frame;
	t_error			err;

	err = error(ERR_NO);
	while (redirector->stack.len > 0)
	{
		err = redirect_stack_get_current_frame(&redirector->stack, &frame);
		if (err.type)
			return (err);
		redirector->stack.len--;
		err = fd_restore_frame(redirector, frame);
		if (err.type)
			return (err);
	}
	return (err);
}

t_error	fd_restore_last_backup(t_redirector *redirector)
{
	t_redir_frame	*frame;
	t_redir_backup	*backup;
	t_error			err;

	err = redirect_stack_get_current_frame(&redirector->stack, &frame);
	if (err.type)
		return (err);
	err = redirect_frame_get_current_backup(frame, &backup);
	if (err.type)
		return (err);
	frame->len--;
	return (fd_restore_fds(redirector, backup));
}

t_error	fd_restore_last_frame(t_redirector *redirector)
{
	t_redir_frame	*frame;
	t_error			err;

	err = redirect_stack_get_current_frame(&redirector->stack, &frame);
	if (err.type)
		return (err);
	redirector->stack.len--;
	return (fd_restore_frame(redirector, frame));
}
