#include "token_recognition_priv.h"
#include "token_recognition_context.h"

t_error	recognize_token_quoting_context(t_lexer *lexer, t_context context)
{
	return (token_recognize_consume_context(lexer, context));
}
