/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   posix_write.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:43:41 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 12:43:42 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "posix_helpers.h"
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <unistd.h>

static inline t_error	write_handle_result(
	ssize_t ret,
	size_t requested,
	size_t *written,
	bool *retry)
{
	*written = 0;
	*retry = false;
	if (ret < 0 && errno == EINTR)
	{
		*retry = true;
		return (error(ERR_NO));
	}
	if (ret < 0 || (ret == 0 && requested != 0))
		return (error(ERR_POSIX_WRITE));
	*written = (size_t)ret;
	return (error(ERR_NO));
}

t_error	posix_write(int fd, const char *buff, size_t len)
{
	size_t	chunk_len;
	size_t	written;
	ssize_t	ret;
	bool	retry;
	t_error	err;

	while (len > 0)
	{
		if (len > (size_t)SSIZE_MAX)
			chunk_len = (size_t)SSIZE_MAX;
		else
			chunk_len = len;
		ret = write(fd, buff, chunk_len);
		err = write_handle_result(ret, chunk_len, &written, &retry);
		if (err.type)
			return (err);
		if (retry)
			continue ;
		buff += written;
		len -= written;
	}
	return (error(ERR_NO));
}
