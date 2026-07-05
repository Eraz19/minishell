#include "scanner_recognition_.h"

t_error	lexer_rule_blank(t_lexer *lexer)
{
	if (lexer->token->type != TOKEN_NONE)
		return (lexer_delimit_token(lexer), lexer->err);
	while (is_blank(lexer->input->str.data[lexer->input->i]) &&
		lexer->input->str.data[lexer->input->i] != '\0')
		lexer->input->i++;
	return (lexer->err);
}
