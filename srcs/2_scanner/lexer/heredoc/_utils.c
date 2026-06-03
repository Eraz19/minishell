/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 19:32:45 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/02 16:24:10 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "expander.h"
#include "_heredoc.h"

bool	is_line_delimiter(t_lexer *state, t_heredoc_body *body)
{
	size_t	delim_len;
	char	*delim_str;
	char	*trimmed_line;

	delim_str = buff_get_string(&body->delim);
	if (delim_str == NULL)
		return (state->err = ERR_LIBC, true);
	delim_len = str_len(delim_str);
	if (body->mode == TAB_STRIP)
	{
		trimmed_line = str_trim_leading(body->line, "\t");
		if (trimmed_line == NULL)
			return (state->err = ERR_LIBC, true);
		free(body->line);
		body->line = trimmed_line;
	}
	return (!str_ncmp(body->line, delim_str, delim_len));
}

t_error	heredoc_consume_line(t_lexer *state, t_heredoc_body *body)
{
	if (body == NULL || state == NULL || body->line == NULL)
		return (state->err = ERR_NULL_ARGS, state->err);
	else if (*body->line == '\0')
		return (state->err);
	body->reached_here_end = is_line_delimiter(state, body);
	if (state->err)
		return (state->err);
	if (!body->reached_here_end)
	{
		if (!buff_append(&body->content, body->line, (long)str_len(body->line)))
			return (state->err = ERR_LIBC, state->err);
		free(body->line);
		body->line = NULL;
	}
	return (state->err);
}

void	heredoc_advance(t_heredoc_body *body, size_t len)
{
	if (body->reached_end_of_input)
	{
		body->i = 0;
		free(body->input);
		body->input = NULL;
		body->reached_end_of_input = false;
	}
	else
		body->i += len;
}

t_error	heredoc_read_tty_line(t_lexer *state, t_heredoc_body *body)
{
	if (body == NULL || state == NULL)
		state->err = ERR_NULL_ARGS;
	else
		state->err = reader_heredoc(&body->input);
	return (body->i = 0, state->err);
}

t_error	heredoc_build_delimiter(t_lexer *state, t_heredoc_body *body)
{
	t_buff	delim;

	if (!buff_init(&delim, 0, NULL, 0))
		return (ERR_LIBC);
	state->err = expander_quote_remove(&delim, &body->delim);
	if (state->err)
		return (buff_free(&delim), state->err);
	if (!buff_append(&delim, "\n", 1))
		return (buff_free(&delim), ERR_LIBC);
	return (buff_free(&body->delim), body->delim = delim, ERR_NO);
}
