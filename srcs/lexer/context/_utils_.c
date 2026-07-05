#include "lexer.h"

t_error	context_EOI(t_lexer *lexer)
{
	if (lexer->rules.on_eoi != NULL)
		return (lexer->rules.on_eoi(lexer));
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
