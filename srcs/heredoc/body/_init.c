/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 09:13:33 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/15 11:13:35 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "heredoc_body_.h"
#include "heredoc_queue_.h"

void	heredoc_body_init(t_heredoc_body *state)
{
	*(state) = (t_heredoc_body){0};
	buff_init(&state->content, 0, NULL, 0);
}

void	heredoc_body_free(t_heredoc_body *state)
{
	buff_free(&state->content);
	heredoc_queue_item_free(state->item);
	if (state->input != NULL)
		free(state->input);
	if (state->line != NULL)
		free(state->line);
	*(state) = (t_heredoc_body){0};
}

t_error	heredoc_body_load(
	t_heredoc_body *state,
	t_heredoc_queue_item *item,
	char *input,
	size_t *i)
{
	state->i = i;
	state->item = item;
	if (input != NULL)
	{
		state->input = str_dup(input);
		if (state->input == NULL)
			return (state->err = ERR_LIBC);
	}
	return (state->err);
}
