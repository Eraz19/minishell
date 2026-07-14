#include "lexer.h"
#include "expander_.h"

t_error	str_escape(t_lexer *lexer)
{
	t_escape_args	args;

	args.is_in_special_context = NULL;
	args.is_in_special_whitelist = NULL;
	args.enable_line_continuation = true;
	args.is_in_whitelist = is_in_context_none_whitelist;
	return (lexer_context_escape(lexer, args));
}

t_error	str_unescape(t_lexer *lexer, void *_)
{
	t_unescape_args	args;

	args.special_args = NULL;
	args.special_handler = NULL;
	return (lexer_context_unescape(lexer, args));
}

t_lexer_context_args	str_context_rules(void)
{
	t_lexer_context_args	res;

	res.unescaped_args = NULL;
	res.escape = str_escape;
	res.is_end = is_context_none_ending;
	res.unescaped = str_unescape;
	res.quoting = lexer_rule_quoting;
	res.is_quoting = is_quoting_context;
	res.expansion = lexer_rule_expansion;
	res.is_expansion = is_substitution_context;
	return (res);
}
