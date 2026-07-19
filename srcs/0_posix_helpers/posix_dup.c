#include "error.h"
#include "posix_helpers.h"
#include <errno.h>
#include <unistd.h>

/*
** POSIX.1-2024 / XSH dup:
** dup() is specified as equivalent to fcntl(fildes, F_DUPFD, 0), and POSIX
** lists EBADF and EMFILE as dup() errors, but does not list EINTR.
**
** The EINTR retry below is therefore defensive only: if an implementation ever
** reports an interrupted dup(), retrying is safe because no new fd was returned
** to the shell, so the fd tracker has not acquired any new ownership yet.
*/
t_error	posix_dup(int fd, int *out)
{
	*out = -1;
	while (true)
	{
		*out = dup(fd);
		if (*out != -1)
			return (error(ERR_NO));
		else if (errno == EINTR)
			continue ;
		return (error_sys());
	}
}

t_error	posix_dup2(int fd_from, int fd_to)
{
	while (dup2(fd_from, fd_to) == -1)
	{
		if (errno == EINTR)
			continue ;
		return (error_sys());
	}
	return (error(ERR_NO));
}
