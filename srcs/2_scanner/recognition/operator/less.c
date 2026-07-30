#include "scanner_recognition_.h"
# include <assert.h>

bool	is_operator_char_less(t_lexer *lexer)
{
	if (lexer->token->type == TOKEN_LESS)
		return (true);
	else if (!is_in_middle_of_operator(lexer))
		return (true);
	return (false);
}

t_error	operator_add_less(t_lexer *lexer)
{
	if (lexer->token->type == TOKEN_LESS)
		return (lexer_consume(lexer, TOKEN_DLESS, 1));
	else if (lexer->token->type == TOKEN_NONE)
		return (lexer_consume(lexer, TOKEN_LESS, 1));
	assert(false);
}
