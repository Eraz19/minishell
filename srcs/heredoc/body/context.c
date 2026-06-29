#include "lexer.h"

/*
** A here-document body whose delimiter is unquoted is expanded like the inside
** of double quotes: parameter, command and arithmetic expansions are active,
** single and double quotes are literal, and a backslash keeps its meaning only
** before '$', '`', '\\' (and a newline, as a line continuation). The top-level
** scan therefore detects expansions only, leaving quoting to the constructs
** that re-enable it (e.g. inside a command substitution).
*/
static t_error	heredoc_body_escape(t_lexer *state)
{
	t_escape_args	args;

	args.is_in_special_context = NULL;
	args.is_in_special_whitelist = NULL;
	args.enable_line_continuation = true;
	args.is_in_whitelist = is_in_context_dquote_whitelist;
	return (lexer_context_escape(state, args));
}

static t_error	heredoc_body_unescape(t_lexer *state, void *unused)
{
	t_unescape_args	args;

	(void)unused;
	args.special_args = NULL;
	args.special_handler = NULL;
	return (lexer_context_unescape(state, args));
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
	res.is_expansion = is_expansion_context;
	return (res);
}
