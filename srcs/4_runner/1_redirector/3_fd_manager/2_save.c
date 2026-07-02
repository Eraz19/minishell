#include "posix_helpers.h"
#include "fd_tracker.h"
#include "redirect_stack.h"
#include "redirector_type.h"
#include "fd_manager.h"

void	fd_save_perm(t_redirector *redirector, int fd)
{
	fd_tracker_mark_perm(&redirector->tracker, fd);
}

t_error	fd_save_temp(t_redirector *redirector, int fd)
{
	t_redir_backup	backup;
	t_error			err;

	backup.fd = fd;
	err = fd_tracker_mark_temp(&redirector->tracker, fd);
	if (err.type)
		return (err);
	err = fd_tracker_backup(&redirector->tracker, fd, &backup.backup_fd);
	if (err.type)
		return (fd_tracker_unlock(&redirector->tracker, fd), err);
	err = redirect_frame_push(&redirector->stack, &backup);
	if (err.type)
	{
		fd_tracker_unlock(&redirector->tracker, backup.fd);
		fd_tracker_unlock(&redirector->tracker, backup.backup_fd);
		if (backup.backup_fd >= 0)
			(void)posix_close_if_open(backup.backup_fd);
	}
	return (err);
}
