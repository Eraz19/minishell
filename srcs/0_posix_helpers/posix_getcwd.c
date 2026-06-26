#include "error.h"
#include "posix_helpers.h"
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFF_INITIAL_CAP	128

static t_error	getcwd_grow_size(size_t *size)
{
	if (*size > SIZE_MAX / 2)
		return (error(ERR_SIZE_MAX_REACHED));
	*size *= 2;
	return (error(ERR_NO));
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
		free(buff);
		if (err.saved_errno != ERANGE)
			return (err);
		err = getcwd_grow_size(&size);
		if (err.type)
			return (err);
	}
}
