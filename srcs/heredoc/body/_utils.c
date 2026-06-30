#include "heredoc_body_.h"

t_error	heredoc_body_escape(t_lexer *state)
{
	t_escape_args	args;

	args.is_in_special_context = NULL;
	args.is_in_special_whitelist = NULL;
	args.enable_line_continuation = true;
	args.is_in_whitelist = is_in_context_dquote_whitelist;
	return (lexer_context_escape(state, args));
}

t_error	heredoc_body_unescape(t_lexer *state, void *unused)
{
	t_unescape_args	args;

	(void)unused;
	args.special_args = NULL;
	args.special_handler = NULL;
	return (lexer_context_unescape(state, args));
}

t_error	get_heredoc_body_line(t_heredoc_body *state, char *EOL, size_t *i)
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
	return (string_cmp(&state->line, &state->item->delim));
}
