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
			error(ERR_SIZE_MAX_REACHED),
			"posix_getcwd()",
			"unable to grow buffer");
		return (false);
	}
	*size *= 2;
	return (true);
}

t_error	posix_getcwd(char **dst)
{
	char	*buff;
	size_t	size;
	t_error	err;

	*dst = NULL;
	size = BUFF_INITIAL_CAP;
	while (true)
	{
		buff = malloc(size);
		if (!buff)
			return (error_sys());
		if (getcwd(buff, size))
			return (*dst = buff, error(ERR_NO));
		err = error_sys();
		if (err.saved_errno == EACCES)
		{
			(void)str_lcpy(buff, PWD_UNSPECIFIED_VALUE, size);
			return (*dst = buff, error(ERR_NO));
		}
		free(buff);
		if (err.saved_errno != ERANGE)
			return (err);
		if (!posix_getcwd_grow_size(&size))
			return (error(ERR_SIZE_MAX_REACHED));
	}
}
