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
		if (state->item->input[*state->item->i] == '\0')
		{
			if (state->item->is_tty)
				scanner_read_continuation(&state->item->input);
			else
				return (state->err = error(ERR_NO_DELIM));
		}
		match_EOL = str_chr(state->item->input + *state->item->i, '\n');
		if (heredoc_body_extract_line(state, match_EOL, state->item->i).type)
			return (state->err);
		if (is_line_delimiter(state))
			return (state->err);
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
