/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 19:21:20 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/10 16:49:10 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "reader_.h"
#include "heredoc_body_.h"

static t_error	heredoc_body_tty_EOI(t_heredoc_body *state, size_t *i)
{
	state->line = str_dup(state->input + *i);
	if (state->line == NULL)
		return (state->err = ERR_LIBC, state->err);
	return (*i = 0, free(state->input), state->input = NULL, state->err);
}

t_error	heredoc_body_content_no_tty(t_heredoc_body *state)
{
	char	*match_EOL;

	while (true)
	{
		match_EOL = str_chr(state->input + *state->no_tty.i, '\n');
		if (match_EOL == NULL)
			return (state->err = ERR_NO_DELIM, state->err);
		else if (heredoc_body_line(state, match_EOL, state->no_tty.i))
			return (state->err);
		if (!is_line_delimiter(state) && heredoc_body_add_line(state))
			return (state->err);
		else
			return (state->err);
	}
}

t_error	heredoc_body_content_tty(t_heredoc_body *state)
{
	size_t	i;
	char	*match_EOL;

	i = 0;
	while (true)
	{
		if (state->input == NULL)
		{
			state->err = reader_heredoc(&state->input);
			if (state->err)
				return (state->err);
		}
		match_EOL = str_chr(state->input + i, '\n');
		if (match_EOL == NULL && heredoc_body_tty_EOI(state, &i))
			return (state->err);
		else if (heredoc_body_line(state, match_EOL, &i))
			return (state->err);
		if (!is_line_delimiter(state))
		{
			if (heredoc_body_add_line(state))
				return (state->err);
		}
		else
			return (state->err);
	}
}

t_error	heredoc_body_save_content(t_heredoc_body *state)
{
	int	fd;

	fd = open(state->path, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		return (state->err = ERR_LIBC, state->err);
	if (write(fd, state->content.data, state->content.len) == -1)
		state->err = ERR_LIBC;
	return (close(fd), state->err);
}
