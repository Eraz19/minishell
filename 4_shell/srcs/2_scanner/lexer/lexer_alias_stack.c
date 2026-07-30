#include "lexer.h"
#include "lexer_priv.h"

t_error	lexer_push_alias(t_lexer *lexer, t_lexer_input_stack_item *alias)
{
	t_token	*out;

	lexer->err = lexer_input_stack_push(&lexer->input_stack, alias);
	if (lexer->err.type)
		return (lexer->err);
	lexer_input_stack_get_last(&lexer->input_stack, &lexer->input);
	out = lexer->token;
	token_free(out);
	unbind_lexer_token(lexer);
	return (lexer_get_next_token(lexer, out));
}

t_error	lexer_pop_alias(t_lexer *lexer)
{
	t_token	*out;

	lexer_input_stack_pop(&lexer->input_stack);
	lexer_input_stack_get_last(&lexer->input_stack, &lexer->input);
	if (lexer->token->type != TOKEN_EOF)
		return (lexer->err);
	out = lexer->token;
	token_free(out);
	unbind_lexer_token(lexer);
	return (lexer_get_next_token(lexer, out));
}
