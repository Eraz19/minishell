#include <fcntl.h>
#include <unistd.h>
#include "scanner.h"
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

t_error	heredoc_body_get_content(t_heredoc_body *state)
{
	char	*match_EOL;

	while (true)
	{
		if (state->input[*state->i] == '\0')
		{
			if (state->is_stdin)
				scanner_read_continuation(&state->input);
			else
				return (state->err = error(ERR_NO_DELIM));
		}
		match_EOL = str_chr(state->input + *state->i, '\n');
		if (heredoc_body_extract_line(state, match_EOL, state->i).type)
			return (state->err);
		if (is_line_delimiter(state))
			return (state->err);
		else if (heredoc_body_line_to_content(state).type)
			return (state->err);
	}
}

t_error	heredoc_body_store(t_heredoc *state, t_heredoc_queue_item *item)
{
	t_heredoc_body	body;

	heredoc_body_init(&body);
	if (heredoc_body_load(&body, item, state->is_stdin).type)
		return (heredoc_body_free(&body), state->err = body.err);
	if (heredoc_body_get_content(&body).type)
		return (heredoc_body_free(&body), state->err = body.err);
	if (heredoc_body_save_content(&body).type)
		return (heredoc_body_free(&body), state->err = body.err);
	return (heredoc_body_free(&body), state->err);
}
