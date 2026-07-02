#include "posix_helpers.h"
#include <errno.h>

t_error	posix_close_if_open(int fd)
{
	t_error	err;

	if (fd < 0)
		return (error(ERR_NO));
	err = posix_close(fd);
	if (err.saved_errno == EBADF)
		return (error(ERR_NO));
	return (err);
}
