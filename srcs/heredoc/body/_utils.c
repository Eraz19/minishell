#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "heredoc_body_.h"

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
	if (state->item->mode == HEREDOC_MODE_TAB_STRIP)
	{
		trimmed_line = str_trim_leading(state->line, "\t");
		if (trimmed_line == NULL)
			return (state->err = error_sys(), true);
		free(state->line);
		state->line = trimmed_line;
	}
	return (!str_ncmp(state->line, state->item->delim, delim_len));
}
