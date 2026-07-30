#include "scanner_recognition_.h"
# include <assert.h>

bool	is_operator_char_semicolon(t_lexer *lexer)
{
	if (lexer->token->type == TOKEN_SCOLON)
		return (true);
	else if (!is_in_middle_of_operator(lexer))
		return (true);
	return (false);
}

t_error	operator_add_semicolon(t_lexer *lexer)
{
	if (lexer->token->type == TOKEN_SCOLON)
		return (lexer_consume(lexer, TOKEN_DSEMI, 1));
	else if (lexer->token->type == TOKEN_NONE)
		return (lexer_consume(lexer, TOKEN_SCOLON, 1));
	assert(false);
}
