#include "alias.h"
#include "lexer_.h"

static t_error	lexer_input_EOF(t_lexer *state)
{
	state->input = NULL;
	state->err = input_stack_pop(&state->input_stack);
	if (state->err.type)
		return (state->err);
	return (state->err = alias_on_expansion_end(), state->err);
}

t_error	lexer_next_token(t_lexer *state, t_token *token)
{
	t_context	context;

	state->emited_token = false;
	if (state->input == NULL)
	{
		state->err = input_stack_get_last(&state->input_stack, &state->input);
		if (state->err.type)
			return (state->err);
	}
	token_init(token);
	state->token = token;
	if (state->input_stack.len == 1)
		state->token->index.start = (ssize_t)state->input->i;
	while (!state->emited_token)
	{
		if (lexer_rules(state, &context).type)
			return (state->err);
	}
	if (token->type == TOKEN_EOF && state->input_stack.len > 0)
		lexer_input_EOF(state);
	return (state->err);
}
