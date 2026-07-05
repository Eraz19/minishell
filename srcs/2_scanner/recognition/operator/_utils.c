#include "scanner_recognition_.h"

bool	is_in_middle_of_operator(t_lexer *lexer)
{
	return (lexer->token->type != TOKEN_NONE
		&& lexer->token->type != TOKEN_TOKEN);
}
