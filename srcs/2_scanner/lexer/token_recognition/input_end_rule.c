#include "token_recognition_priv.h"

t_error	recognize_token_input_end(t_lexer *lexer)
{
	token_recognition_delimit(lexer);
	if (lexer->token->type == TOKEN_NONE)
		lexer->token->type = TOKEN_EOF;
	return (lexer->err);
}
