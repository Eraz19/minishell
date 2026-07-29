#include "generator_serialize_priv.h"
#include "libft.h"
#include <stdbool.h>
#include <stddef.h>
#include <limits.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

bool	generator_write(int fd, const char *buff)
{
	size_t	len;
	size_t	chunk_len;
	ssize_t	written;

	len = str_len(buff);
	while (len > 0)
	{
		if (len > (size_t)SSIZE_MAX)
			chunk_len = (size_t)SSIZE_MAX;
		else
			chunk_len = len;
		written = write(fd, buff, chunk_len);
		if (written < 0 && errno == EINTR)
			continue ;
		else if (written == 0)
			errno = EIO;
		if (written <= 0)
			return (serializer_report_failure(), false);
		buff += written;
		len -= (size_t)written;
	}
	return (true);
}

bool	generator_write_zu(int fd, const char *opt_prefix, size_t value)
{
	char	*converted;

	if (opt_prefix != NULL && generator_write(fd, opt_prefix) == false)
		return (false);
	converted = ft_zutoa(value);
	if (converted == NULL)
		return (serializer_report_failure());
	else if (generator_write(fd, converted) == false)
		return (free(converted), false);
	free(converted);
	return (true);
}
