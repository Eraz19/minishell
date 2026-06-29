#include "lexer.h"

static t_error	context_start(t_lexer *state, t_lexer_context_args args)
{
	state->token->type = TOKEN_TOKEN;
	if (args.stack_item != NULL)
		args.stack_item->start = state->token->value.len;
	state->err = context_stack_push(&state->input->context, args.stack_item);
	if (state->err.type)
		return (state->err);
	return (lexer_consume(state, state->token->type, args.opening_len));
}

static t_error	context_end(t_lexer *state, t_lexer_context_args args)
{
	t_context_parser_stack_item	*item;

	if (lexer_consume(state, state->token->type, args.closing_len).type)
		return (state->err);
	state->err = context_stack_bpop(&state->input->context, &item);
	if (state->err.type)
		return (state->err);
	return (item->end = state->token->value.len, state->err);
}

t_error	lexer_context_unescape(t_lexer *state, t_unescape_args args)
{
	if (state->input->str.data[state->input->i] == '\0')
		return (context_EOI(state));
	else if (args.special_handler != NULL)
		return (args.special_handler(state, args.special_args));
	else
		return (lexer_consume(state, state->token->type, 1));
}

t_error	lexer_context_escape(t_lexer *state, t_escape_args args)
{
	state->token->type = TOKEN_TOKEN;
	if (args.enable_line_continuation &&
		state->input->str.data[state->input->i + 1] == '\n')
	{
		lexer_advance(state, 2);
		if (state->input->str.data[state->input->i] == '\0')
			return (context_EOI(state));
	}
	else if (state->input->str.data[state->input->i] == '\0')
		return (context_EOI(state));
	else
	{
		if (lexer_consume(state, state->token->type, 1).type)
			return (state->err);	
		if (context_escape_next_char(state, args).type)
			return (state->err);
	}
	return (state->err);
}

t_error	lexer_context_scan(t_lexer *state, t_lexer_context_args args)
{
	char		*str;
	t_context	context;

	if (context_start(state, args).type)
		return (state->err);
	while (true)
	{
		if (state->err.type)
			return (state->err);
		str = state->input->str.data + state->input->i;
		if (args.is_end != NULL && args.is_end(*str, args.unescaped_args))
			return (context_end(state, args));
		else if (*str == '\\')
			args.escape(state);
		else if (args.quoting != NULL && args.is_quoting(str, &context))
			args.quoting(state, context);
		else if (args.expansion != NULL && args.is_expansion(str, &context))
			args.expansion(state, context);
		else
			args.unescaped(state, args.unescaped_args);
	}
}
