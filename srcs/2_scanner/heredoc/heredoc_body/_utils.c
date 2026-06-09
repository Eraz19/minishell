/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 11:15:15 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/05 19:32:50 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "__heredoc_body.h"

t_error	heredoc_body_add_line(t_heredoc_body *state)
{
	size_t	line_len;

	line_len = str_len(state->line);
	if (!buff_append(&state->content, state->line, (long)line_len))
		return (state->err = ERR_LIBC, state->err);
	return (free(state->line), state->line = NULL, state->err);
}

t_error	heredoc_body_line(t_heredoc_body *state, char *EOL, size_t *i)
{
	char	*start;
	size_t	line_len;

	start = state->input + *i;
	*i += (size_t)(EOL - start) + 1;
	line_len = (size_t)(EOL - start) + 1;
	state->line = str_sub(start, 0, line_len);
	if (state->line == NULL)
		state->err = ERR_LIBC;
	return (state->err);
}

bool	is_line_delimiter(t_heredoc_body *state)
{
	size_t	delim_len;
	char	*trimmed_line;

	delim_len = str_len(state->delim);
	if (state->mode == TAB_STRIP)
	{
		trimmed_line = str_trim_leading(state->line, "\t");
		if (trimmed_line == NULL)
			return (state->err = ERR_LIBC, true);
		free(state->line);
		state->line = trimmed_line;
	}
	return (!str_ncmp(state->line, state->delim, delim_len));
}
