#include "redirect_priv.h"
#include "posix_helpers.h"
#include <errno.h>

t_error	redirect_create_backup(t_redir_backup *backup, int fd)
{
	t_error	err;

	backup->fd = fd;
	err = posix_dup(fd, &backup->backup_fd);
	if (err.type == ERR_LIBC && err.saved_errno == EBADF)
		return (error(ERR_NO));
	else if (err.type && backup->backup_fd >= 0)
		(void)posix_close(backup->backup_fd);
	return (err);
}

t_error	redirect_restore_fds(t_redir_backup *backup)
{
	t_error	err;

	if (backup == NULL)
		return (error(ERR_NO));
	if (backup->backup_fd == -1)
	{
		err = posix_close(backup->fd);
		if (err.type == ERR_LIBC && err.saved_errno == EBADF)
			return (error(ERR_NO));
		return (err);
	}
	err = posix_dup2(backup->backup_fd, backup->fd);
	(void)posix_close(backup->backup_fd);
	return (err);
}
