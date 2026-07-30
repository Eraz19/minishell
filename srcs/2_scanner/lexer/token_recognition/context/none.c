#include <stdlib.h>
#include "token_recognition.h"
#include "token_recognition_priv.h"
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

t_error	none_context_unescape_rules(t_lexer *lexer, void *_)
{
	t_token_recognition_unescape	args;

	args.lexer = lexer;
	args.special_args = NULL;
	args.special_handler = NULL;
	return (scan_context_unescape(args));
}

t_token_recognition_context	none_context_rules(t_lexer *lexer, t_context_stack_item	*item)
{
	return ((t_token_recognition_context)
		{
			.lexer = lexer,
			.context_item = item,
			.opening_len = 0,
			.closing_len = 0,
			.quoting = recognize_token_quoting_context,
			.is_quoting = is_quoting_context_start,
			.expansion = recognize_token_expansion_context,
			.is_expansion = is_expansion_context_start,
			.unescaped_args = NULL,
			.unescaped = none_context_unescape_rules,
			.escape = none_context_escape_rules,
			.is_end = is_context_none_ending,
		}
	);
}

t_error	scan_none_context(t_lexer *lexer)
{
	t_context_stack_item	*item;

	lexer->err = context_stack_item_init(&item, CONTEXT_NONE);
	if (lexer->err.type)
		return (lexer->err);
	lexer->err = context_stack_push(&lexer->token->contexts, item);
	if (lexer->err.type)
		return (free(item), lexer->err);
	return (scan_context(none_context_rules(lexer, item)));
}
