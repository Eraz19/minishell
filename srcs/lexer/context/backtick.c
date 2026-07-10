#include "lexer.h"

static bool	is_backtick_squote_surrounded(t_lexer *lexer)
{
	t_error					err;
	t_context_stack_item	*item;
	
	if (lexer->input->context.len < 2)
		return (false);
	err = context_stack_get(
		&lexer->input->context,
		&item,
		lexer->input->context.len - 2);
    if (err.type)
        return (false);
    return (item->context == CONTEXT_DQUOTE || item->context == CONTEXT_ARITH);
}

static t_error	context_backtick_escape(t_lexer *lexer)
{
	t_escape_args	args;

	args.is_in_whitelist = is_in_context_backtick_whitelist;
	args.is_in_special_context = is_backtick_squote_surrounded;
	args.enable_line_continuation = is_backtick_squote_surrounded(lexer);
	args.is_in_special_whitelist = is_in_context_backtick_special_whitelist;
	return (lexer_context_escape(lexer, args));
}

static t_error	context_backtick_unescape(t_lexer *lexer, void *_)
{
	t_unescape_args	args;

	args.special_args = NULL;
	args.special_handler = NULL;
	return (lexer_context_unescape(lexer, args));
}

static t_lexer_context_args	context_backtick_rules(t_context_stack_item *item)
{
	t_lexer_context_args	res;

	res.opening_len = 1;
	res.closing_len = 1;
	res.stack_item = item;
	res.context = CONTEXT_BACKTICK;
	res.unescaped_args = NULL;
	res.quoting = lexer_rule_quoting;
	res.is_quoting = is_quoting_context;
	res.escape = context_backtick_escape;
	res.expansion = lexer_rule_expansion;
	res.is_expansion = is_substitution_context;
	res.is_end = is_context_backtick_ending;
	res.unescaped = context_backtick_unescape;
	return (res);
}

t_error	lexer_context_backtick(t_lexer *lexer)
{
	t_context_stack_item	*item;

	lexer->err = context_stack_item_init(&item, CONTEXT_BACKTICK);
	if (lexer->err.type)
		return (lexer->err);
	lexer->err = context_stack_push(&lexer->token->contexts, item);
	if (lexer->err.type)
		return (lexer->err);
	return (lexer_context_scan(lexer, context_backtick_rules(item)));
}
