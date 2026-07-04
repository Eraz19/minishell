#include "lexer.h"

static t_error	context_param_escape(t_lexer *lexer)
{
	t_escape_args	args;

	args.is_in_special_context = NULL;
	args.is_in_special_whitelist = NULL;
	args.enable_line_continuation = true;
	args.is_in_whitelist = is_in_context_param_whitelist;
	return (lexer_context_escape(lexer, args));
}

static t_error	context_param_unescape(t_lexer *lexer, void *_)
{
	t_unescape_args	args;

	args.special_args = NULL;
	args.special_handler = NULL;
	return (lexer_context_unescape(lexer, args));
}

static t_lexer_context_args	context_param_rules(t_context_stack_item *item)
{
	t_lexer_context_args	res;

	res.opening_len = 2;
	res.closing_len = 1;
	res.context = CONTEXT_PARAM;
	res.stack_item = item;
	res.unescaped_args = NULL;
	res.quoting = lexer_rule_quoting;
	res.escape = context_param_escape;
	res.is_quoting = is_quoting_context;
	res.is_end = is_context_param_ending;
	res.expansion = lexer_rule_expansion;
	res.unescaped = context_param_unescape;
	res.is_expansion = is_substitution_context;
	return (res);
}

t_error	lexer_context_param(t_lexer *lexer)
{
	t_context_stack_item	*item;

	lexer->err = context_stack_item_init(&item, CONTEXT_PARAM);
	if (lexer->err.type)
		return (lexer->err);
	lexer->err = context_stack_push(&lexer->token->contexts, item);
	if (lexer->err.type)
		return (lexer->err);
	return (lexer_context_scan(lexer, context_param_rules(item)));
}
