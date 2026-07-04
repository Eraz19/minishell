#include "lexer.h"

static t_error	context_dollar_squote_escape(t_lexer *lexer)
{
	t_escape_args	args;

	args.is_in_special_context = NULL;
	args.is_in_special_whitelist = NULL;
	args.enable_line_continuation = false;
	args.is_in_whitelist = is_in_context_dollar_squote_whitelist;
	return (lexer_context_escape(lexer, args));
}

static t_error	context_dollar_squote_unescape(t_lexer *lexer, void *_)
{
	t_unescape_args	args;

	args.special_args = NULL;
	args.special_handler = NULL;
	return (lexer_context_unescape(lexer, args));
}

static t_lexer_context_args	context_dollar_squote_rules(
								t_context_stack_item *item)
{
	t_lexer_context_args	res;

	res.quoting = NULL;
	res.opening_len = 2;
	res.closing_len = 1;
	res.expansion = NULL;
	res.stack_item = item;
	res.is_quoting = NULL;
	res.is_expansion = NULL;
	res.unescaped_args = NULL;
	res.context = CONTEXT_DOLLAR_SQUOTE;
	res.escape = context_dollar_squote_escape;
	res.is_end = is_context_dollar_squote_ending;
	res.unescaped = context_dollar_squote_unescape;
	return (res);
}

t_error	lexer_context_dollar_squote(t_lexer *lexer)
{
	t_context_stack_item	*item;

	lexer->err = context_stack_item_init(&item, CONTEXT_DOLLAR_SQUOTE);
	if (lexer->err.type)
		return (lexer->err);
	lexer->err = context_stack_push(&lexer->token->contexts, item);
	if (lexer->err.type)
		return (lexer->err);
	return (lexer_context_scan(lexer, context_dollar_squote_rules(item)));
}
