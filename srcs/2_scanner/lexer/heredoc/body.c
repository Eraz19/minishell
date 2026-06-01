/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   body.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 19:21:20 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/01 10:56:44 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "expander.h"
#include "../_lexer.h"
#include "../../_scanner.h"

static bool	heredoc_add_line_to_content(t_heredoc_body *body, t_lexer *state)
{
	char	*delim;
	size_t	line_len;

	line_len = str_len(body->last_line);
	delim = buff_get_string(&body->delim);
	if (delim == NULL)
		return (heredoc_body_free(body), true);
	if (!str_ncmp(body->last_line, delim, str_len(delim)))
	{
		state->reached_here_end = true;
		write(body->fd, body->content.data, body->content.len);
		return (heredoc_body_free(body), true);
	}
	else if (!buff_append(&body->content, body->last_line, (long)line_len))
		return (state->err = ERR_LIBC, heredoc_body_free(body), true);
	return (free(body->last_line), true);
}

static bool	heredoc_format_line(t_heredoc_body *body, t_lexer *state)
{
	char	*line;

	if (body->mode == TAB_STRIP)
	{
		line = str_trim_leading(body->last_line, " \t");
		if (line == NULL)
			return (state->err = ERR_LIBC, true);
		return (free(body->last_line), body->last_line = line, false);
	}
	return (true);
}

static bool	heredoc_get_line(char **res, t_lexer *state)
{
	size_t	line_len;
	char	*input_ptr;
	char	*newline_ptr;

	if (state->is_tty)
		return (state->err = reader_heredoc(res), true);
	else
	{
		input_ptr = state->input + state->i;
		newline_ptr = str_chr(input_ptr, '\n');
		if (newline_ptr == NULL)
		{
			*res = str_dup(input_ptr);
			return (state->i += str_len(input_ptr), true);
		}
		else
		{
			line_len = (size_t)(newline_ptr - input_ptr + 1);
			*res = str_sub(input_ptr, 0, line_len);
			return (state->i += line_len, true);
		}
	}
}

static t_error	heredoc_build_delimiter(t_buff *res, t_here_queue_item *item)
{
	t_error	err;
	t_buff	delim;

	if (!buff_init(&delim, 0, NULL, 0))
		return (ERR_LIBC);
	if (!buff_dup_n(&delim, &item->delim, item->delim.len))
		return (ERR_LIBC);
	if (!buff_append(&delim, "\n", 1))
		return (ERR_LIBC);
	err = expander_quote_removal(res, &delim);
	return (buff_free(&delim), err);
}

bool	heredoc_get_body(t_lexer *state, t_here_queue_item *item)
{
	t_heredoc_body	body;

	state->reached_here_end = false;
	state->err = heredoc_build_delimiter(&body.delim, item);
	if (state->err)
		return (true);
	heredoc_body_init(&body);
	state->err = heredoc_body_load(&body, item);
	if (state->err)
		return (heredoc_body_free(&body), true);
	while (!state->reached_here_end)
	{
		if (state->err)
			return (heredoc_body_free(&body), true);
		else if (state->input[state->i] == '\0')
			return (heredoc_body_free(&body), state->err = ERR_NO_DELIM, true);
		else if (heredoc_get_line(&body.last_line, state) && state->err)
			return (heredoc_body_free(&body), true);
		else if (heredoc_format_line(&body, state) && state->err)
			return (heredoc_body_free(&body), true);
		else if (heredoc_add_line_to_content(&body, state) && state->err)
			return (heredoc_body_free(&body), true);
	}
	return (true);
}
