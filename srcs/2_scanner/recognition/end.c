#include "scanner_recognition_.h"

bool	is_end(t_lexer *lexer)
{
	return (lexer->input->str.data[lexer->input->i] == '\0');
}

t_error	lexer_rule_end(t_lexer *lexer)
{

	lexer_delimit_token(lexer);
	if (lexer->token->type == TOKEN_NONE)
		lexer->token->type = TOKEN_EOF;
	return (lexer->err);
}
