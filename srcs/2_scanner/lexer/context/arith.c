#include "lexer_rules_.h"
#include "lexer_context_.h"

static t_error	context_arith_unescape_(t_lexer *state, void *nesting_depth)
{
	if (state->input->str[state->input->i] == '(')
	{
		(*((size_t *)nesting_depth))++;
		if (lexer_consume(state, state->token->type, 1).type)
			return (state->err);
	}
	else if (state->input->str[state->input->i] == ')')
	{
		(*((size_t *)nesting_depth))--;
		if (lexer_consume(state, state->token->type, 1).type)
			return (state->err);
	}
	else
		return (lexer_consume(state, state->token->type, 1));
	return (state->err);
}

static t_error	context_arith_escape(t_lexer *state)
{
	t_escape_args	args;

	args.is_in_special_context = NULL;
	args.is_in_special_whitelist = NULL;
	args.enable_line_continuation = true;
	args.is_in_whitelist = is_in_context_dquote_whitelist;
	return (lexer_context_escape(state, args));
}

static t_error	context_arith_unescape(t_lexer *state, void *nesting_depth)
{
	t_unescape_args	args;
	
	args.special_args = nesting_depth;
	args.special_handler = context_arith_unescape_;
	return (lexer_context_unescape(state, args));
}

static t_lexer_context_args	context_arith_rules(
	size_t *nesting_depth,
	t_context_parser_stack_item *item)
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
	res.is_expansion = is_expansion_context;
	return (res);
}

t_error	lexer_context_arith(t_lexer *state)
{
	t_lexer_context_args			args;
	t_context_parser_stack_item	*item;
	t_lexer_backup			backup;
	size_t					nesting_depth;

	nesting_depth = 0;
	backup = lexer_backup(state);
	state->err = context_parser_stack_item_init(&item, CONTEXT_ARITH);
	if (state->err.type)
		return (state->err);
	state->err = context_stack_push(&state->token->contexts, item);
	if (state->err.type)
		return (state->err);
	args = context_arith_rules(&nesting_depth, item);
	if (lexer_context_scan(state, args).type)
		return (state->err);
	if (state->input->str[state->input->i] != ')')
	{
		if (lexer_restore(state, backup).type)
			return (state->err);
		return (state->err = error(ERR_CTX_END_NOT_FOUND), state->err);
	}
	if (lexer_consume(state, state->token->type, 1).type)
		return (state->err);
	return (item->end = state->token->value.len, state->err);
}
