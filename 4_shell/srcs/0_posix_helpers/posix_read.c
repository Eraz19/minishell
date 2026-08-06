#include "error.h"
#include "posix_helpers.h"
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <unistd.h>

#define CHUNK_LEN	128

// @ret ERR_NO / ERR_LIBC
static inline t_error	posix_read(
							int fd,
							void *buff,
							size_t len,
							size_t *bytes_read)
{
	size_t	chunk_len;
	ssize_t	ret;

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
			continue ;
		return (error_sys());
	}
}

t_error	posix_read_all(int fd, t_string *out)
{
	t_buff	buff;
	size_t	read;
	t_error	err;

	(void)buff_init(&buff, 0, NULL, 0);
	while (true)
	{
		if (!buff_grow(&buff, buff.cap + CHUNK_LEN))
			return (err = error_sys(), buff_free(&buff), err);
		err = posix_read(fd, buff.data + buff.len, buff.cap - buff.len, &read);
		if (err.type)
			return (buff_free(&buff), err);
		else if (read == 0)
			break ;
		buff.len += read;
	}
	if (!buff_append_n(&buff, "", 1))
		return (err = error_sys(), buff_free(&buff), err);
	string_take(out, buff.data, buff.cap, (ssize_t)buff.len - 1);
	return (err);
}

t_error	posix_read_until_c(int fd, t_string *out, char c)
{
	t_buff	buff;
	size_t	read;
	t_error	err;

	(void)buff_init(&buff, 0, NULL, 0);
	while (true)
	{
		if (!buff_grow(&buff, buff.cap + 1))
			return (err = error_sys(), buff_free(&buff), err);
		err = posix_read(fd, buff.data + buff.len, 1, &read);
		if (err.type)
			return (buff_free(&buff), err);
		else if (read == 0)
			break ;
		buff.len += read;
		if (buff.data[buff.len - 1] == c)
			break ;
	}
	if (!buff_append_n(&buff, "", 1))
		return (err = error_sys(), buff_free(&buff), err);
	string_take(out, buff.data, buff.cap, (ssize_t)buff.len - 1);
	return (err);
}
