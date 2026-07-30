#include <assert.h> // DEBUG
#include "token_recognition_priv.h"
#include "token_recognition_operator.h"

bool	is_char_ampersand_fit_operator(t_lexer *lexer)
{
	if (lexer->token->type == TOKEN_SCOLON)
		return (true);
	else if (lexer->token->type == TOKEN_AMPERSAND)
		return (true);
	else if (lexer->token->type == TOKEN_LESS)
		return (true);
	else if (lexer->token->type == TOKEN_GREAT)
		return (true);
	else if (!is_inside_operator(lexer))
		return (true);
	return (false);
}

t_error	token_recognition_consume_ampersand(t_lexer *lexer)
{
	if (lexer->token->type == TOKEN_SCOLON)
		return (token_recognition_consume(lexer, TOKEN_SEMI_AND, 1));
	else if (lexer->token->type == TOKEN_AMPERSAND)
		return (token_recognition_consume(lexer, TOKEN_AND_IF, 1));
	else if (lexer->token->type == TOKEN_LESS)
		return (token_recognition_consume(lexer, TOKEN_LESSAND, 1));
	else if (lexer->token->type == TOKEN_GREAT)
		return (token_recognition_consume(lexer, TOKEN_GREATAND, 1));
	else if (lexer->token->type == TOKEN_NONE)
		return (token_recognition_consume(lexer, TOKEN_AMPERSAND, 1));
	assert(false);
	return (error(ERR_NO));
}
