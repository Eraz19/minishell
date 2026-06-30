#include <fcntl.h>
#include "scanner.h"
#include "heredoc_body_.h"

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

static t_error	get_heredoc_body_content(t_heredoc_body *state)
{
	char	*match_EOL;
	bool	used_continuation;

	used_continuation = false;
	while (true)
	{
		if (state->item->input.data[state->i] == '\0')
		{
			if (heredoc_body_continuation(state, &used_continuation).type)
				return (state->err);
		}
		match_EOL = str_chr(state->item->input.data + state->i, '\n');
		if (get_heredoc_body_line(state, match_EOL, &state->i).type)
			return (state->err);
		if (is_line_delimiter(state))
		{
			if (!used_continuation)
				*state->item->i = state->i;
			return (state->err);
		}
		if (!string_append(&state->content, &state->line))
			return (state->err = error_sys());
		string_free(&state->line);
	}
}

t_error	read_heredoc_body_from_input(
			t_heredoc *state,
			t_heredoc_queue_item *item)
{
	t_heredoc_body	body;

	heredoc_body_init(&body);
	heredoc_body_load(&body, item);
	state->err = get_heredoc_body_content(&body);
	if (state->err.type)
		return (heredoc_body_free(&body), state->err);
	state->err = heredoc_save_body_in_file(&body.item->path, &body.content);
	return (heredoc_body_free(&body), state->err);
}

t_lexer_context_args	heredoc_body_context_rules(void)
{
	t_lexer_context_args	res;

	res.quoting = NULL;
	res.is_quoting = NULL;
	res.unescaped_args = NULL;
	res.escape = heredoc_body_escape;
	res.is_end = is_context_none_ending;
	res.unescaped = heredoc_body_unescape;
	res.expansion = lexer_rule_expansion;
	res.is_expansion = is_substitution_context;
	return (res);
}
