/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 10:25:27 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/08 10:34:28 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "__history_file.h"

t_error	history_file_write(t_history_file *state, char *entry)
{
	int	fd;

	if (history_file_open(state, &fd, O_WRONLY | O_APPEND))
		return (state->err);
	if (write(fd, entry, str_len(entry)) == -1)
		return (close(fd), state->err = ERR_LIBC, state->err);
	return (close(fd), state->err);
}

t_error	history_file_read(t_history_file *state, char **content)
{
	int		fd;
	t_buff	content_buff;

	if (history_file_open(state, &fd, O_RDONLY))
		return (state->err);
	buff_init(&content_buff, 0, NULL, 0);
	if (!buff_read_all(&content_buff, fd))
		return (buff_free(&content_buff), state->err = ERR_LIBC, state->err);
	close(fd);
	*content = buff_get_string(&content_buff);
	if (*content == NULL)
		return (buff_free(&content_buff), state->err = ERR_LIBC, state->err);
	return (buff_free(&content_buff), state->err);
}
