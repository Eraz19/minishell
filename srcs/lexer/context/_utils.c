#include "lexer.h"

static t_error	context_start(t_lexer *lexer, t_lexer_context_args args)
{
	lexer->token->type = TOKEN_TOKEN;
	if (args.stack_item != NULL)
		args.stack_item->start = lexer->token->value.len;
	lexer->err = context_stack_push(&lexer->input->context, args.stack_item);
	if (lexer->err.type)
		return (lexer->err);
	return (lexer_consume(lexer, lexer->token->type, args.opening_len));
}

static t_error	context_end(t_lexer *lexer, t_lexer_context_args args)
{
	t_context_stack_item	*item;

	if (lexer_consume(lexer, lexer->token->type, args.closing_len).type)
		return (lexer->err);
	lexer->err = context_stack_bpop(&lexer->input->context, &item);
	if (lexer->err.type)
		return (lexer->err);
	return (item->end = lexer->token->value.len, lexer->err);
}

t_error	lexer_context_unescape(t_lexer *lexer, t_unescape_args args)
{
	if (lexer->input->str.data[lexer->input->i] == '\0')
		return (context_EOI(lexer));
	else if (args.special_handler != NULL)
		return (args.special_handler(lexer, args.special_args));
	else
		return (lexer_consume(lexer, lexer->token->type, 1));
}

t_error	lexer_context_escape(t_lexer *lexer, t_escape_args args)
{
	lexer->token->type = TOKEN_TOKEN;
	if (args.enable_line_continuation &&
		lexer->input->str.data[lexer->input->i + 1] == '\n')
	{
		lexer_advance(lexer, 2);
		if (lexer->input->str.data[lexer->input->i] == '\0')
			return (context_EOI(lexer));
	}
	else if (lexer->input->str.data[lexer->input->i] == '\0')
		return (context_EOI(lexer));
	else
	{
		if (lexer_consume(lexer, lexer->token->type, 1).type)
			return (lexer->err);	
		if (context_escape_next_char(lexer, args).type)
			return (lexer->err);
	}
	return (lexer->err);
}

t_error	lexer_context_scan(t_lexer *lexer, t_lexer_context_args args)
{
	char		*str;
	t_context	context;

	if (context_start(lexer, args).type)
		return (lexer->err);
	while (true)
	{
		if (lexer->err.type)
			return (lexer->err);
		str = lexer->input->str.data + lexer->input->i;
		if (args.is_end != NULL && args.is_end(*str, args.unescaped_args))
			return (context_end(lexer, args));
		else if (*str == '\\')
			args.escape(lexer);
		else if (args.quoting != NULL && args.is_quoting(str, &context))
			args.quoting(lexer, context);
		else if (args.expansion != NULL && args.is_expansion(str, &context))
			args.expansion(lexer, context);
		else
			args.unescaped(lexer, args.unescaped_args);
	}
}
