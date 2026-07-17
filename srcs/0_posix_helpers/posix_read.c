#include "error.h"
#include "posix_helpers.h"
#include "shell.h"
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <unistd.h>

#define CHUNK_LEN	128

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
			return (*bytes_read = (size_t)ret, error(ERR_NO));
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

t_error	posix_read_all(int fd, t_string *out)
{
	size_t	read;
	t_error	err;

	(void)string_init(out, 0, NULL, 0);
	while (true)
	{
		if (!string_grow(out, out->cap + CHUNK_LEN))
			return (err = error_sys(), string_free(out), err);
		err = posix_read(fd, out->data + out->len, out->cap - out->len, &read);
		if (err.type)
			return (string_free(out), err);
		else if (read == 0)
			break ;
		out->len += read;
	}
	if (!string_append_n(out, "", 0))
		return (err = error_sys(), string_free(out), err);
	return (err);
}
