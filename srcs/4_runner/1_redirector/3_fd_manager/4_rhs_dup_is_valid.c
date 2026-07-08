#include "redirector_type.h"
#include "fd_manager.h"
#include "fd_tracker.h"
#include <errno.h>
#include <sys/stat.h>

t_error	fd_check_dup_rhs(t_redirector *redirector, int fd)
{
	struct stat	info;

	if (fd_tracker_fd_is_used_by_shell(&redirector->tracker, fd))
		return (error(ERR_POSIX_REDIRECTION));
	if (fstat(fd, &info) == 0)
		return (error(ERR_NO));
	else if (errno == EBADF)
		return (error(ERR_POSIX_REDIRECTION));
	return (error_sys());
}
