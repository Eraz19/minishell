#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "heredoc_body_.h"
#include "libft.h"

t_error	heredoc_body_line_to_content(t_heredoc_body *state)
{
	if (!string_append(&state->content, &state->line))
		return (state->err = error_sys());
	return (string_free(&state->line), state->err);
}

t_error	heredoc_body_extract_line(t_heredoc_body *state, char *EOL, size_t *i)
{
	char	*start;
	size_t	line_len;

	start = state->item->input.data + *i;
	*i += (size_t)(EOL - start) + 1;
	line_len = (size_t)(EOL - start) + 1;
	if (!string_init(&state->line, 0, start, (long)line_len))
		return (state->err = error_sys());
	return (state->err);
}

bool	is_line_delimiter(t_heredoc_body *state)
{
	if (state->item->mode == HEREDOC_MODE_TAB_STRIP)
		string_trim_leading(&state->line, '\t');
	return (!string_cmp(&state->line, &state->item->delim));
}
