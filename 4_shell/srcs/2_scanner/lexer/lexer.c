#include <stdlib.h>
#include "lexer.h"
#include "lexer_priv.h"
#include "lexer_input_stack.h"
#include "token_recognition.h"
#include "token_recognition_context_scan.h"

t_error	lexer_get_next_token(t_lexer *lexer, t_token *out)
{
	bind_lexer_input(lexer);
	if (recognize_token(lexer, out).type)
		return (unbind_lexer_token(lexer), lexer->err);
	if (out->type == TOKEN_EOF && lexer->input_stack.len > 1)
		return (lexer_pop_alias(lexer));
	return (unbind_lexer_token(lexer), lexer->err);
}

t_error	lexer_scan_word(t_lexer *lexer, t_token *out, t_token_recognition_context *args)
{
	bind_lexer_input(lexer);
	bind_lexer_token(lexer, out);
	if (scan_context(*args).type)
		return (free(args->context_item), unbind_lexer_token(lexer), lexer->err);
	return (free(args->context_item), unbind_lexer_token(lexer), lexer->err);
}
