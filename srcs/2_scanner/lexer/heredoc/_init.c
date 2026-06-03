/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 09:13:33 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/02 15:30:28 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "_heredoc.h"

void	heredoc_body_init(t_heredoc_body *state)
{
	*(state) = (t_heredoc_body){0};
	buff_init(&state->delim, 0, NULL, 0);
	buff_init(&state->content, 0, NULL, 0);
}

void	heredoc_body_free(t_heredoc_body *state)
{
	buff_free(&state->delim);
	buff_free(&state->content);
	if (state->input != NULL)
		free(state->input);
	if (state->line != NULL)
		free(state->line);
	if (state->fd != 0)
		close(state->fd);
	*(state) = (t_heredoc_body){0};
}

t_error	heredoc_body_load(t_heredoc_body *state, t_here_queue_item *item)
{
	if (state == NULL || item == NULL)
		return (ERR_NULL_ARGS);
	buff_dup_n(&state->delim, &item->delim, item->delim.len);
	if (state->delim.data == NULL)
		return (ERR_LIBC);
	state->mode = item->mode;
	state->fd = open(item->path, O_WRONLY);
	if (state->fd == -1)
		return (ERR_LIBC);
	return (ERR_NO);	
}
