#include "scanner_recognition_.h"
# include <assert.h>

bool	is_operator_char_ampersand(t_lexer *lexer)
{
	if (lexer->token->type == TOKEN_SCOLON)
		return (true);
	else if (lexer->token->type == TOKEN_AMPERSAND)
		return (true);
	else if (lexer->token->type == TOKEN_LESS)
		return (true);
	else if (lexer->token->type == TOKEN_GREAT)
		return (true);
	else if (!is_in_middle_of_operator(lexer))
		return (true);
	return (false);
}

t_error	operator_add_ampersand(t_lexer *lexer)
{
	if (lexer->token->type == TOKEN_SCOLON)
		return (lexer_consume(lexer, TOKEN_SEMI_AND, 1));
	else if (lexer->token->type == TOKEN_AMPERSAND)
		return (lexer_consume(lexer, TOKEN_AND_IF, 1));
	else if (lexer->token->type == TOKEN_LESS)
		return (lexer_consume(lexer, TOKEN_LESSAND, 1));
	else if (lexer->token->type == TOKEN_GREAT)
		return (lexer_consume(lexer, TOKEN_GREATAND, 1));
	else if (lexer->token->type == TOKEN_NONE)
		return (lexer_consume(lexer, TOKEN_AMPERSAND, 1));
	assert(false);
}
