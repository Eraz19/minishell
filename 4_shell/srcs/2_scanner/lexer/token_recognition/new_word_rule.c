#include "token_recognition_priv.h"
#include "token_recognition_context.h"

t_error	recognize_token_new_word(t_lexer *lexer) // Rule 10
{
	if (lexer->input->str.data[lexer->input->i] == '\\')
		return (none_context_escape_rules(lexer));
	else
		return (token_recognition_consume(lexer, TOKEN_TOKEN, 1));
}
