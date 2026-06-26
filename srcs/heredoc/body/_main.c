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

static t_error	heredoc_body_continuation(
	t_heredoc_body *state,
	bool *used_continuation)
{
	if (state->item->is_tty)
	{
		if (*used_continuation == false)
			*state->item->i = state->i;
		*used_continuation = true;
		return (scanner_read_continuation(&state->item->input), state->err);
	}
	else
		return (state->err = error(ERR_NO_DELIM));
}

static t_error	heredoc_body_get_content(t_heredoc_body *state)
{
	char	*match_EOL;
	bool	used_continuation;

	used_continuation = false;
	while (true)
	{
		if (state->item->input[state->i] == '\0')
		{
			if (heredoc_body_continuation(state, &used_continuation).type)
				return (state->err);
		}
		match_EOL = str_chr(state->item->input + state->i, '\n');
		if (heredoc_body_extract_line(state, match_EOL, &state->i).type)
			return (state->err);
		if (is_line_delimiter(state))
		{
			if (!used_continuation)
				*state->item->i = state->i;
			return (state->err);
		}
		else if (heredoc_body_line_to_content(state).type)
			return (state->err);
	}
}

t_error	heredoc_body_read(t_heredoc *state, t_heredoc_queue_item *item)
{
	t_heredoc_body	body;

	heredoc_body_init(&body);
	heredoc_body_load(&body, item);
	if (heredoc_body_get_content(&body).type)
		state->err = body.err;
	else if (heredoc_body_save_content(&body).type)
		state->err = body.err;
	return (heredoc_body_free(&body), state->err);
}
