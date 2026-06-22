#include "alias.h"
#include "lexer_.h"

t_error	lexer_next_token(t_lexer *state, t_token *token)
{
	t_context	context;

	state->emited_token = false;
	state->err = input_stack_get_last(&state->input_stack, &state->input);
	if (state->err.type)
		return (state->err);
	token_init(token);
	state->token = token;
	while (!state->emited_token)
	{
		if (lexer_rules(state, &context).type)
			return (state->err);
	}
	if (token->type == TOKEN_EOF && state->input_stack.len > 0)
	{
		state->err = input_stack_pop(&state->input_stack);
		if (state->err.type)
			return (state->err);
		state->err = alias_on_expansion_end();
		if (state->err.type)
			return (state->err);
	}
	return (state->input = NULL, state->err);
}
