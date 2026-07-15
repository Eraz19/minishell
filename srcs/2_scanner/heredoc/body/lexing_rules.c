#include "lexer.h"

t_error	body_escape(t_lexer *lexer)
{
	t_escape_args	args;

	args.is_in_special_context = NULL;
	args.is_in_special_whitelist = NULL;
	args.enable_line_continuation = true;
	args.is_in_whitelist = is_in_context_heredoc_whitelist;
	return (lexer_context_escape(lexer, args));
}

t_error	body_unescape(t_lexer *lexer, void *_)
{
	t_unescape_args	args;

	args.special_args = NULL;
	args.special_handler = NULL;
	return (lexer_context_unescape(lexer, args));
}
