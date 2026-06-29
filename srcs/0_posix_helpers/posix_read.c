#include "error.h"
#include "posix_helpers.h"
#include "shell.h"
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <unistd.h>

t_error	posix_read(int fd, void *buff, size_t len, size_t *bytes_read)
{
	size_t	chunk_len;
	ssize_t	ret;
	t_error	err;

	*bytes_read = 0;
	if (len > (size_t)SSIZE_MAX)
		chunk_len = (size_t)SSIZE_MAX;
	else
		chunk_len = len;
	while (true)
	{
		ret = read(fd, buff, chunk_len);
		if (ret >= 0)
		{
			*bytes_read = (size_t)ret;
			return (error(ERR_NO));
		}
		if (errno == EINTR)
		{
			err = shell_should_interrupt();
			if (err.type)
				return (err);
			continue ;
		}
		return (error_sys());
	}
}
