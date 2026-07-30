#include <stdlib.h>
#include "token_recognition_context.h"
#include "token_recognition_context_scan.h"

t_error	dollar_squote_context_escape_rules(t_lexer *lexer)
{
	t_token_recognition_escape	args;

	args.lexer = lexer;
	args.line_continuation = false;
	args.is_in_special_context = NULL;
	args.is_in_special_whitelist = NULL;
	args.is_in_whitelist = is_in_context_dollar_squote_whitelist;
	return (scan_context_escape(args));
}

t_error	dollar_squote_context_unescape_rules(t_lexer *lexer, void *_)
{
	t_token_recognition_unescape	args;

	args.lexer = lexer;
	args.special_args = NULL;
	args.special_handler = NULL;
	return (scan_context_unescape(args));
}

t_token_recognition_context	dollar_squote_context_rules(t_lexer *lexer, t_context_stack_item *item)
{
	return ((t_token_recognition_context)
		{
			.lexer = lexer,
			.context_item = item,
			.opening_len = 2,
			.closing_len = 1,
			.quoting = NULL,
			.is_quoting = NULL,
			.expansion = NULL,
			.is_expansion = NULL,
			.unescaped_args = NULL,
			.unescaped = dollar_squote_context_unescape_rules,
			.escape = dollar_squote_context_escape_rules,
			.is_end = is_context_dollar_squote_ending,
		}
	);
}

t_error	scan_dollar_squote_context(t_lexer *lexer)
{
	t_context_stack_item	*item;

	lexer->err = context_stack_item_init(&item, CONTEXT_DOLLAR_SQUOTE);
	if (lexer->err.type)
		return (lexer->err);
	lexer->err = context_stack_push(&lexer->token->contexts, item);
	if (lexer->err.type)
		return (free(item), lexer->err);
	return (scan_context(dollar_squote_context_rules(lexer, item)));
}
