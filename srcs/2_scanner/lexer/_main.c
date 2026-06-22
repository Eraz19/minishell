#include "lexer_.h"

t_error	lexer_next_token(t_lexer *state, t_token *token)
{
	t_context	context;

	state->reached_EOI = false;
	state->emited_token = false;
	state->err = input_stack_get_last(&state->input_stack, &state->input);
	if (state->err.type)
		return (state->err);
	token_init(token);
	state->token = token;
	while (!state->emited_token && !state->reached_EOI)
	{
		if (lexer_rules(state, &context).type)
			return (state->err);
	}
	if (state->reached_EOI)
		state->err = input_stack_pop(&state->input_stack);
	return (state->input = NULL, state->err);
}
