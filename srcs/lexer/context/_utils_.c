#include "lexer.h"

static const char	*unterminated_construct(t_lexer *lexer)
{
	t_context_stack_item	*item;

	if (lexer->input == NULL || lexer->input->context.len == 0)
		return (NULL);
	if (context_stack_get(&lexer->input->context, &item,
			lexer->input->context.len - 1).type)
		return (NULL);
	if (item->context == CONTEXT_SQUOTE)
		return ("unterminated single quotes");
	if (item->context == CONTEXT_DQUOTE)
		return ("unterminated double quotes");
	if (item->context == CONTEXT_DOLLAR_SQUOTE)
		return ("unterminated $'...' quotes");
	if (item->context == CONTEXT_BACKTICK)
		return ("unterminated backquote substitution");
	if (item->context == CONTEXT_CMD_SUB)
		return ("unterminated command substitution");
	if (item->context == CONTEXT_ARITH)
		return ("unterminated arithmetic expansion");
	if (item->context == CONTEXT_PARAM)
		return ("unterminated parameter expansion");
	return (NULL);
}

t_error	context_EOI(t_lexer *lexer)
{
	const char	*construct;

	if (lexer->rules.on_eoi != NULL)
		return (lexer->rules.on_eoi(lexer));
	construct = unterminated_construct(lexer);
	if (construct != NULL)
		return (lexer->err = error_print(error(ERR_UNEXPECTED_EOI),
				"lexer", construct, NULL, NULL));
	return (lexer->err = error(ERR_UNEXPECTED_EOI));
}

t_error	context_escape_next_char(t_lexer *lexer, t_escape_args args)
{
	bool	in_special_context;

	in_special_context = false;
	if (args.is_in_special_context != NULL)
		in_special_context = args.is_in_special_context(lexer);
	if (in_special_context && args.is_in_special_whitelist != NULL)
	{
		if (args.is_in_special_whitelist(
				lexer->input->str.data[lexer->input->i]))
			lexer_consume(lexer, lexer->token->type, 1);
	}
	else if (!in_special_context && args.is_in_whitelist != NULL)
	{
		if (args.is_in_whitelist(lexer->input->str.data[lexer->input->i]))
			lexer_consume(lexer, lexer->token->type, 1);
	}
	else
		lexer->err = error(ERR_INCOHERENT_STATE);
	return (lexer->err);
}
