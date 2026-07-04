#include "lexer.h"

static t_error	context_dquote_escape(t_lexer *lexer)
{
	t_escape_args	args;

	args.is_in_special_context = NULL;
	args.is_in_special_whitelist = NULL;
	args.enable_line_continuation = true;
	args.is_in_whitelist = is_in_context_dquote_whitelist;
	return (lexer_context_escape(lexer, args));
}

static t_error	context_dquote_unescape(t_lexer *lexer, void *_)
{
	t_unescape_args	args;

	args.special_args = NULL;
	args.special_handler = NULL;
	return (lexer_context_unescape(lexer, args));
}

static t_lexer_context_args	context_dquote_rules(t_context_stack_item *item)
{
	t_lexer_context_args	res;

	res.quoting = NULL;
	res.opening_len = 1;
	res.closing_len = 1;
	res.context = CONTEXT_DQUOTE;
	res.stack_item = item;
	res.is_quoting = NULL;
	res.unescaped_args = NULL;
	res.escape = context_dquote_escape;
	res.expansion = lexer_rule_expansion;
	res.is_end = is_context_dquote_ending;
	res.unescaped = context_dquote_unescape;
	res.is_expansion = is_substitution_context;
	return (res);
}

t_error	lexer_context_dquote(t_lexer *lexer)
{
	t_context_stack_item	*item;

	lexer->err = context_stack_item_init(&item, CONTEXT_DQUOTE);
	if (lexer->err.type)
		return (lexer->err);
	lexer->err = context_stack_push(&lexer->token->contexts, item);
	if (lexer->err.type)
		return (lexer->err);
	return (lexer_context_scan(lexer, context_dquote_rules(item)));
}
