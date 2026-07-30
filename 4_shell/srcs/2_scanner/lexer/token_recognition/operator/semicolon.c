#include <assert.h> // DEBUG
#include "token_recognition_priv.h"
#include "token_recognition_operator.h"

bool	is_char_semicolon_fit_operator(t_lexer *lexer)
{
	if (lexer->token->type == TOKEN_SCOLON)
		return (true);
	else if (!is_inside_operator(lexer))
		return (true);
	return (false);
}

t_error	token_recognition_consume_semicolon(t_lexer *lexer)
{
	if (lexer->token->type == TOKEN_SCOLON)
		return (token_recognition_consume(lexer, TOKEN_DSEMI, 1));
	else if (lexer->token->type == TOKEN_NONE)
		return (token_recognition_consume(lexer, TOKEN_SCOLON, 1));
	else
		return (lexer->err = error(ERR_POSIX_SYNTAX));
}
