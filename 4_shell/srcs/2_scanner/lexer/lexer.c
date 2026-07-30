#include <stdlib.h>
#include "lexer.h"
#include "lexer_priv.h"
#include "lexer_input_stack.h"
#include "token_recognition.h"

t_error	lexer_get_next_token(t_lexer *lexer, t_token *out)
{
	if (lexer->input == NULL && bind_lexer_input(lexer, NULL).type)
		return (lexer->err);
	if (recognize_token(lexer, out).type)
		return (unbind_lexer_token(lexer), lexer->err);
	if (out->type == TOKEN_EOF && lexer->input_stack.len > 1)
		return (lexer_pop_alias(lexer));
	return (unbind_lexer_token(lexer), lexer->err);
}
