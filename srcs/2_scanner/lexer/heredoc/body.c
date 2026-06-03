/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   body.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 19:21:20 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/02 16:26:31 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../../_scanner.h"

static t_error	heredoc_get_body_not_tty(t_lexer *state, t_heredoc_body *body)
{
	size_t	line_len;
	char	*cursor;
	char	*match_eol;

	while (!body->reached_here_end)
	{
		cursor = state->input + state->i + body->i;
		match_eol = str_chr(cursor, '\n');
		if (match_eol == NULL)
			return (state->err = ERR_NO_DELIM, state->err);
		line_len = (size_t)(match_eol - cursor) + 1;
		body->line = str_sub(cursor, 0, line_len);
		if (body->line == NULL)
			return (state->err = ERR_LIBC, state->err);
		if (heredoc_consume_line(state, body))
			return (state->err);
		heredoc_advance(body, line_len);
		free(body->line);
		body->line = NULL;
	}
	return (state->err);
}

static t_error	heredoc_tty_next_line(t_heredoc_body *body, size_t *line_len)
{
	char	*match_eol;

	body->line = body->input + body->i;
	match_eol = str_chr(body->line, '\n');
	if (match_eol == NULL)
	{
		*line_len = str_len(body->line);
		body->line = str_dup(body->line);
		if (body->line == NULL)
			return (ERR_LIBC);
		body->reached_end_of_input = true;
	}
	else
	{
		*line_len = (size_t)(match_eol - body->line) + 1;
		body->line = str_sub(body->line, 0, *line_len);
	}
	if (body->line == NULL)
		return (ERR_LIBC);
	return (ERR_NO);
}

static t_error	heredoc_get_body_tty(t_lexer *state, t_heredoc_body *body)
{
	size_t	line_len;

	while (!body->reached_here_end)
	{
		if (body->input == NULL && heredoc_read_tty_line(state, body))
			return (state->err);
		state->err = heredoc_tty_next_line(body, &line_len);
		if (state->err)
			return (state->err);
		if (heredoc_consume_line(state, body))
			return (state->err);
		heredoc_advance(body, line_len);
	}
	return (state->err);
}

bool	heredoc_get_body(t_lexer *state, t_here_queue_item *item)
{
	t_heredoc_body	body;

	heredoc_body_init(&body);
	state->err = heredoc_body_load(&body, item);
	if (state->err)
		return (heredoc_body_free(&body), true);
	if (heredoc_build_delimiter(state, &body))
		return (heredoc_body_free(&body), true);
	else if (state->is_tty && heredoc_get_body_tty(state, &body))
		return (heredoc_body_free(&body), true);
	else if (!state->is_tty && heredoc_get_body_not_tty(state, &body))
		return (heredoc_body_free(&body), true);
	if (!state->is_tty)
		state->i += body.i;
	if (write(body.fd, body.content.data, body.content.len) == -1)
		state->err = ERR_LIBC;
	return (heredoc_body_free(&body), true);
}
