#include "error.h"
#include "libft.h"
#include "posix_helpers.h"
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFF_INITIAL_CAP	128

static bool	posix_getcwd_grow_size(size_t *size)
{
	if (*size > SIZE_MAX / 2)
	{
		error_print(
			"posix_getcwd()",
			"unable to grow buffer",
			ERR_SIZE_MAX_REACHED);
		return (false);
	}
	*size *= 2;
	return (true);
}

t_error	posix_getcwd(char **dst)
{
	char	*buff;
	size_t	size;
	int		saved_errno;

	*dst = NULL;
	size = BUFF_INITIAL_CAP;
	while (true)
	{
		buff = malloc(size);
		if (!buff)
			return (ERR_LIBC);
		if (getcwd(buff, size))
			return (*dst = buff, ERR_NO);
		saved_errno = errno;
		if (saved_errno == EACCES)
		{
			(void)str_lcpy(buff, PWD_UNSPECIFIED_VALUE, size);
			return (*dst = buff, ERR_NO);
		}
		free(buff);
		if (saved_errno != ERANGE)
			return (ERR_LIBC);
		if (!posix_getcwd_grow_size(&size))
			return (ERR_SIZE_MAX_REACHED);
	}
}
