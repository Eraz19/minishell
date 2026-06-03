/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 17:11:04 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/03 13:34:06 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "_history.h"

static t_error	history_open_file(int *fd, const char *path, int flags)
{
	if (fd == NULL || path == NULL)
		return (ERR_NULL_ARGS);
	*fd = open(path, flags, 0644);
	if (*fd == -1 && errno != ENOENT)
		return (ERR_LIBC);
	if (*fd == -1)
	{
		*fd = open(path, O_CREAT | flags, 0644);
		if (*fd == -1)
			return (ERR_LIBC);
	}
	return (ERR_NO);
}

t_error	history_read_file(char **content, t_history *state)
{
	int		fd;
	t_buff	content_buff;

	if (content == NULL || state == NULL || state->path == NULL)
		return (ERR_NULL_ARGS);
	state->err = history_open_file(&fd, state->path, O_RDONLY);
	if (state->err)
		return (state->err);
	if (!buff_init(&content_buff, 0, NULL, 0))
		return (state->err = ERR_LIBC, state->err);
	if (!buff_read_all(&content_buff, fd))
		return (buff_free(&content_buff), state->err = ERR_LIBC, state->err);
	close(fd);
	*content = buff_get_string(&content_buff);
	if (*content == NULL)
		state->err = ERR_LIBC;
	return (buff_free(&content_buff), state->err);
}

t_error	history_write_in_file(t_history *state, char *entry)
{
	int	fd;
	
	if (state == NULL || entry == NULL)
		return (state->err = ERR_NULL_ARGS, state->err);
	state->err = history_open_file(&fd, state->path, O_WRONLY | O_APPEND);
	if (state->err)
		return (state->err);
	if (write(fd, entry, str_len(entry)) == -1)
		return (close(fd), state->err = ERR_LIBC, state->err);
	return (close(fd), state->err);
}
