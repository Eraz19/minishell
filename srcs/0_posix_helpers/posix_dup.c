#include "error.h"
#include "posix_helpers.h"
#include "shell.h"
#include <errno.h>
#include <unistd.h>

t_error	posix_dup(int fd, int *out)
{
	t_error	err;

	*out = -1;
	while (*out == -1)
	{
		*out = dup(fd);
		if (*out == -1)
		{
			err = error_sys();
			if (err.saved_errno == EINTR)
			{
				err = shell_should_interrupt();
				if (err.type)
					return (err);
				continue ;
			}
			return (err);
		}
	}
	return (error(ERR_NO));
}

t_error	posix_dup2(int fd_from, int fd_to)
{
	t_error	err;

	while (dup2(fd_from, fd_to) == -1)
	{
		err = error_sys();
		if (err.saved_errno == EINTR)
		{
			err = shell_should_interrupt();
			if (err.type)
				return (err);
			continue ;
		}
		return (err);
	}
	return (error(ERR_NO));
}
