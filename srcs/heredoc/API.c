/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   API.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 10:37:07 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/19 16:25:12 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "shell.h"
#include "heredoc_.h"
#include "heredoc_body_.h"
#include "heredoc_queue_.h"

t_error	heredoc_store_all(char *input, size_t *start)
{
	t_heredoc_queue_item	item;
	t_heredoc				*state;

	state = shell_get_heredoc();
	if (state == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	while (state->queue.len != 0)
	{
		state->err = heredoc_queue_pop(&state->queue, &item);
		if (state->err.type)
			return (state->err);
		if (state->is_stdin)
			heredoc_body_store(state, &item, NULL, NULL);
		else
			heredoc_body_store(state, &item, input, start);
		if (state->err.type)
			return (state->err);
	}
	return (state->err);
}

t_error	heredoc_add_to_queue(char **path, char *delim, t_heredoc_mode mode)
{
	t_heredoc_queue_item	item;
	t_heredoc				*state;

	state = shell_get_heredoc();
	if (state == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	if (heredoc_create_file(state, path).type)
		return (state->err);
	item.path = str_dup(*path);
	if (item.path == NULL)
		return (free(*path), state->err = error_sys());
	item.delim = str_dup(delim);
	if (item.delim == NULL)
		return (free(*path), free(item.path), state->err = error_sys());
	if (heredoc_build_delimiter(state, &item.delim).type)
		return (free(*path), heredoc_queue_item_free(&item), state->err);
	item.mode = mode;
	state->err = heredoc_queue_push(&state->queue, item);
	if (state->err.type)
		return (free(*path), heredoc_queue_item_free(&item), state->err);
	return (state->err);
}
