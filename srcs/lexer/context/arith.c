#include "lexer.h"

static t_error	context_arith_unescape_(t_lexer *lexer, void *nesting_depth)
{
	if (lexer->input->str.data[lexer->input->i] == '(')
	{
		(*((size_t *)nesting_depth))++;
		if (lexer_consume(lexer, lexer->token->type, 1).type)
			return (lexer->err);
	}
	else if (lexer->input->str.data[lexer->input->i] == ')')
	{
		(*((size_t *)nesting_depth))--;
		if (lexer_consume(lexer, lexer->token->type, 1).type)
			return (lexer->err);
	}
	else
		return (lexer_consume(lexer, lexer->token->type, 1));
	return (lexer->err);
}

static t_error	context_arith_escape(t_lexer *lexer)
{
	t_escape_args	args;

	args.is_in_special_context = NULL;
	args.is_in_special_whitelist = NULL;
	args.enable_line_continuation = true;
	args.is_in_whitelist = is_in_context_dquote_whitelist;
	return (lexer_context_escape(lexer, args));
}

static t_error	context_arith_unescape(t_lexer *lexer, void *nesting_depth)
{
	t_unescape_args	args;
	
	args.special_args = nesting_depth;
	args.special_handler = context_arith_unescape_;
	return (lexer_context_unescape(lexer, args));
}

static t_lexer_context_args	context_arith_rules(
								size_t *nesting_depth,
								t_context_stack_item *item)
{
	t_lexer_context_args	res;

	res.quoting = NULL;
	res.opening_len = 3;
	res.closing_len = 1;
	res.stack_item = item;
	res.is_quoting = NULL;
	res.context = CONTEXT_ARITH;
	res.escape = context_arith_escape;
	res.unescaped_args = nesting_depth;
	res.is_end = is_context_arith_ending;
	res.expansion = lexer_rule_expansion;
	res.unescaped = context_arith_unescape;
	res.is_expansion = is_substitution_context;
	return (res);
}

t_error	lexer_context_arith(t_lexer *lexer)
{
	t_lexer_context_args			args;
	t_context_stack_item	*item;
	t_lexer_backup			backup;
	size_t					nesting_depth;

	nesting_depth = 0;
	backup = lexer_backup(lexer);
	lexer->err = context_stack_item_init(&item, CONTEXT_ARITH);
	if (lexer->err.type)
		return (lexer->err);
	lexer->err = context_stack_push(&lexer->token->contexts, item);
	if (lexer->err.type)
		return (lexer->err);
	args = context_arith_rules(&nesting_depth, item);
	if (lexer_context_scan(lexer, args).type)
		return (lexer->err);
	if (lexer->input->str.data[lexer->input->i] != ')')
	{
		if (lexer_restore(lexer, backup).type)
			return (lexer->err);
		return (lexer->err = error(ERR_CTX_END_NOT_FOUND), lexer->err);
	}
	if (lexer_consume(lexer, lexer->token->type, 1).type)
		return (lexer->err);
	return (item->end = lexer->token->value.len, lexer->err);
}
