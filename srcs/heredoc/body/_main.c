#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "reader_.h"
#include "heredoc_body_.h"

t_error	heredoc_body_get_content_no_tty(t_heredoc_body *state)
{
	char	*match_EOL;

	if (state->input == NULL)
		return (state->err = error(ERR_NO_DELIM));
	while (true)
	{
		match_EOL = str_chr(state->input + *state->i, '\n');
		if (match_EOL == NULL)
			return (state->err = error(ERR_NO_DELIM));
		else if (heredoc_body_extract_line(state, match_EOL, state->i).type)
			return (state->err);
		if (is_line_delimiter(state))
			return (state->err);
		else if (heredoc_body_line_to_content(state).type)
			return (state->err);
	}
}

static t_error	heredoc_body_tty_EOI(t_heredoc_body *state, size_t *i)
{
	state->line = str_dup(state->input + *i);
	if (state->line == NULL)
		return (state->err = error_sys());
	return (*i = 0, free(state->input), state->input = NULL, state->err);
}

t_error	heredoc_body_get_content_tty(t_heredoc_body *state)
{
	size_t	i;
	char	*match_EOL;

	i = 0;
	while (true)
	{
		if (state->input == NULL)
		{
			state->err = reader_heredoc(&state->input);
			if (state->err.type)
				return (state->err);
		}
		match_EOL = str_chr(state->input + i, '\n');
		if (match_EOL == NULL)
		{
			if (heredoc_body_tty_EOI(state, &i).type)
				return (state->err);
		}
		else if (heredoc_body_extract_line(state, match_EOL, &i).type)
			return (state->err);
		if (is_line_delimiter(state))
			return (state->err);
		else if (heredoc_body_line_to_content(state).type)
			return (state->err);
	}
}

t_error	heredoc_body_store(
	t_heredoc *state,
	t_heredoc_queue_item *item,
	char *input,
	size_t *start)
{
	t_heredoc_body	body;

	heredoc_body_init(&body);
	if (heredoc_body_load(&body, item, input, start).type)
		return (heredoc_body_free(&body), state->err = body.err);
	if (!state->is_stdin)
	{
		if (heredoc_body_get_content_no_tty(&body).type)
			return (heredoc_body_free(&body), state->err = body.err);
	}
	else
	{
		if (heredoc_body_get_content_tty(&body).type)
			return (heredoc_body_free(&body), state->err = body.err);
	}
	if (heredoc_body_save_content(&body).type)
		return (heredoc_body_free(&body), state->err = body.err);
	return (heredoc_body_free(&body), state->err);
}
