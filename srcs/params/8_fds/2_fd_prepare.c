#include "fd.h"
#include "fd_tracker.h"
#include "params.h"

// @ret ERR_INTERNAL / ERR_REDIRECTION / ERR_LIBC
t_error	fd_prepare_perm(int fd)
{
	t_fd_manager	*fd_manager;
	t_error			err;

	if (fd < TRACKER_MIN_FD_SHELL)
		return (error(ERR_NO));
	err = params_get_fd_manager(&fd_manager);
	if (err.type == ERR_NO)
		err = fd_tracker_protect(&fd_manager->tracker, fd);
	if (err.type)
		return (err);
	return (fd_tracker_grow(&fd_manager->tracker, (size_t)fd + 1));
}
