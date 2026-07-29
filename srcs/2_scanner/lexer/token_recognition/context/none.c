#include "token_recognition_context.h"
#include "token_recognition_context_scan.h"

t_error	none_context_escape_rules(t_lexer *lexer)
{
	t_token_recognition_escape	args;

	args.lexer = lexer;
	args.line_continuation = true;
	args.is_in_special_context = NULL;
	args.is_in_special_whitelist = NULL;
	args.is_in_whitelist = is_in_context_none_whitelist;
	return (scan_context_escape(args));
}
