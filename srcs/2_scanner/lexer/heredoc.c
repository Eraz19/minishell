/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 17:59:16 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/01 11:25:54 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include "../_scanner.h"
#include "../reader/_reader.h"
#include "./heredoc/_heredoc.h"
#include "./heredoc/here_queue/_here_queue.h"

static t_error	heredoc_build_tmp_path(int i, t_buff path, t_buff *tmp_path)
{
	char	*id;

	id = ft_itoa(i);
	if (id == NULL)
		return (ERR_LIBC);
	if (!buff_dup_n(tmp_path, &path, path.len))
		return (ERR_LIBC);
	if (!buff_append(tmp_path, id, (long)str_len(id)))
		return (buff_free(tmp_path), ERR_LIBC);
	return (free(id), ERR_NO);
}

static t_error	heredoc_create_file(t_file_path res)
{
	int	fd;

	fd = open(res, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (ERR_LIBC);
	return (close(fd), ERR_NO);
}

t_error	lexer_heredoc_create_tmp_file(t_file_path *res)
{
	int		i;
	t_error	err;
	t_buff	path;
	t_buff	tmp_path;

	i = 0;
	err = ERR_NO;
	if (!buff_init(&path, 0, "/tmp/minishell_heredoc_", 23))
		return (ERR_LIBC);
	while (i < INT_MAX)
	{
		err = heredoc_build_tmp_path(i, path, &tmp_path);
		if (err != ERR_NO)
			return (buff_free(&path), err);
		if (!access(buff_get_string(&tmp_path), F_OK))
		{
			heredoc_create_file(buff_get_string(&tmp_path));
			return (*res = buff_get_string(&tmp_path), buff_free(&path), err);
		}
		buff_free(&tmp_path);
		++i;
	}
	return (buff_free(&path), ERR_HEREDOC_FILE_LIMIT);
}

bool	lexer_heredoc_queue_consume(t_lexer *state)
{
	size_t 				i;
	t_here_queue_item	*item;

	i = 0;
	item = NULL;
	while (i < state->queue->len)
	{
		state->err = here_queue_get(item, state->queue, i);
		if (state->err)
			return (true);
		if (heredoc_get_body(state, item) && state->err)
			return (true);
		i++;
	}
	return (here_queue_clean(state->queue), true);
}
