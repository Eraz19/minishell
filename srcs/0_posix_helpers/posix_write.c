#include "error.h"
#include <errno.h>
#include <limits.h>
#include <unistd.h>

t_error	posix_write(int fd, const char *buff, size_t len)
{
	size_t	remaining;
	ssize_t	ret;

	remaining = 0;
	while (len > 0)
	{
		if (len > SSIZE_MAX)
		{
			remaining = len - SSIZE_MAX;
			len -= remaining;
		}
		ret = write(fd, buff, len);
		if (ret < 0 && errno == EINTR)
			continue ;
		else if (ret < 0 || (ret == 0 && len != 0))
			return (ERR_LIBC);
		else if ((size_t)ret == len && remaining == 0)
			return (ERR_NO);
		buff += ret;
		len -= (size_t)ret;
		len += remaining;
		remaining = 0;
	}
	return (ERR_NO);
}
