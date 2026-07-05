#include "scanner_recognition_.h"

bool	is_operator_char_pipe(t_lexer *lexer)
{
	if (lexer->token->type == TOKEN_PIPE)
		return (true);
	else if (lexer->token->type == TOKEN_GREAT)
		return (true);
	else if (!is_in_middle_of_operator(lexer))
		return (true);
	return (false);
}

t_error	operator_add_pipe(t_lexer *lexer)
{
	if (lexer->token->type == TOKEN_PIPE)
		return (lexer_consume(lexer, TOKEN_OR_IF, 1));
	else if (lexer->token->type == TOKEN_GREAT)
		return (lexer_consume(lexer, TOKEN_CLOBBER, 1));
	else if (lexer->token->type == TOKEN_NONE)
		return (lexer_consume(lexer, TOKEN_PIPE, 1));
	return (lexer->err = error(ERR_INCOHERENT_STATE));
}
