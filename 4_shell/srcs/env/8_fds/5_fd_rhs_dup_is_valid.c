#include "fd.h"
#include "fd_tracker.h"
#include "env.h"
#include <errno.h>
#include <sys/stat.h>

// TODO: why ERR_REDIRECTION instead of moving backup away ?
t_error	fd_check_dup_rhs(int fd)
{
	t_fd_manager	*fd_manager;
	struct stat		info;
	t_error			err;

	err = env_get_fd_manager(&fd_manager);
	if (err.type)
		return (err);
	if (fd_tracker_fd_is_used_by_shell(&fd_manager->tracker, fd))
		return (error(ERR_REDIRECTION));
	if (fstat(fd, &info) == 0)
		return (error(ERR_NO));
	else if (errno == EBADF)
		return (error(ERR_REDIRECTION));
	return (error_sys());
}
