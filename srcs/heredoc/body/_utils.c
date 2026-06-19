/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 11:15:15 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/19 16:23:28 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "heredoc_body_.h"

t_error	heredoc_body_save_content(t_heredoc_body *state)
{
	int	fd;

	fd = open(state->item->path, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		return (state->err = error_sys());
	if (write(fd, state->content.data, state->content.len) == -1)
		state->err = error_sys();
	return (close(fd), state->err);
}

t_error	heredoc_body_line_to_content(t_heredoc_body *state)
{
	size_t	line_len;

	line_len = str_len(state->line);
	if (!buff_append(&state->content, state->line, (long)line_len))
		return (state->err = error_sys());
	return (free(state->line), state->line = NULL, state->err);
}

t_error	heredoc_body_extract_line(t_heredoc_body *state, char *EOL, size_t *i)
{
	char	*start;
	size_t	line_len;

	start = state->input + *i;
	*i += (size_t)(EOL - start) + 1;
	line_len = (size_t)(EOL - start) + 1;
	state->line = str_sub(start, 0, line_len);
	if (state->line == NULL)
		state->err = error_sys();
	return (state->err);
}

bool	is_line_delimiter(t_heredoc_body *state)
{
	size_t	delim_len;
	char	*trimmed_line;

	delim_len = str_len(state->item->delim);
	if (state->item->mode == TAB_STRIP)
	{
		trimmed_line = str_trim_leading(state->line, "\t");
		if (trimmed_line == NULL)
			return (state->err = error_sys(), true);
		free(state->line);
		state->line = trimmed_line;
	}
	return (!str_ncmp(state->line, state->item->delim, delim_len));
}
