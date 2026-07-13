#include "scanner_recognition_.h"

bool	is_in_middle_of_operator(t_lexer *lexer)
{
	return (lexer->token->type != TOKEN_NONE
		&& lexer->token->type != TOKEN_TOKEN);
}

t_error	lexer_rule_in_middle_of_operator(t_lexer *lexer) // Rule 2-3
{
	if (is_operator_char(lexer)) // Rule 2
		return (lexer_add_char_into_token_operator(lexer), lexer->err);
	else
		return (lexer_delimit_token(lexer), lexer->err); // Rule 3
}
