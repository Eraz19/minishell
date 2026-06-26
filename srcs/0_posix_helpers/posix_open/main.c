#include "error.h"
#include "posix_helpers.h"
#include "posix_open_priv.h"
#include "shell.h"
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/stat.h>

static inline t_error	posix_open_priv(
	const char *path,
	int oflag,
	mode_t *mode,
	int *out_fd)
{
	t_error	err;

	*out_fd = -1;
	err = open_check_ub_args(oflag, mode);
	if (err.type)
		return (err);
	while (true)
	{
		if (mode)
			*out_fd = open(path, oflag, *mode);
		else
			*out_fd = open(path, oflag);
		if (*out_fd != -1)
			return (error(ERR_NO));
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

t_error	posix_open(const char *path, int oflag, int *out_fd)
{
	return (posix_open_priv(path, oflag, NULL, out_fd));
}

t_error	posix_open_with_mode(
	const char *path,
	int oflag,
	mode_t mode,
	int *out_fd)
{
	return (posix_open_priv(path, oflag, &mode, out_fd));
}
