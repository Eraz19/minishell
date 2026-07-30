#include "token_recognition_priv.h"
#include "token_recognition_operator.h"

t_error	recognize_token_inside_operator(t_lexer *lexer) // Rule 2-3
{
	if (is_operator_char(lexer)) // Rule 2
		return (token_recognition_consume_operator(lexer), lexer->err);
	else
		return (token_recognition_delimit(lexer), lexer->err); // Rule 3
}
