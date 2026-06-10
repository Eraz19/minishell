/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 09:13:33 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/10 16:49:01 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "expander.h"
#include "heredoc_body_.h"

void	heredoc_body_init(t_heredoc_body *state)
{
	*(state) = (t_heredoc_body){0};
	buff_init(&state->content, 0, NULL, 0);
}

void	heredoc_body_free(t_heredoc_body *state)
{
	free(state->delim);
	buff_free(&state->content);
	if (state->input != NULL)
		free(state->input);
	if (state->line != NULL)
		free(state->line);
	*(state) = (t_heredoc_body){0};
}

static t_error	heredoc_build_delimiter(t_heredoc_body *state, t_buff *delim)
{
	t_buff	delim_no_quoting;

	quote_remove(&delim_no_quoting, delim);
	if (state->err)
		return (state->err);
	if (!buff_append(&delim_no_quoting, "\n", 1))
		return (buff_free(&delim_no_quoting), ERR_LIBC);
	state->delim = buff_get_string(&delim_no_quoting);
	if (state->delim == NULL)
		state->err = ERR_LIBC;
	return (buff_free(&delim_no_quoting), state->err);
}

t_error	heredoc_body_load(t_heredoc_body *state, t_heredoc_body_load_args args)
{
	if (heredoc_build_delimiter(state, &args.item->delim))
		return (state->err);
	state->no_tty.i = args.i;
	state->input = args.input;
	state->is_tty = args.is_tty;
	state->mode = args.item->mode;
	state->path = args.item->path;
	return (state->err);
}
