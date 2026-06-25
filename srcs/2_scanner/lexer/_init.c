#include "lexer_.h"

void	lexer_init(t_lexer *state)
{
	*state = (t_lexer){0};
	input_stack_init(&state->input_stack);
}

void	lexer_free(t_lexer *state)
{
	input_stack_free(&state->input_stack);
	*state = (t_lexer){0};
}

void	lexer_load(t_lexer *state, t_lexer_mode mode)
{
	state->mode = mode;
}

void	lexer_reset(t_lexer *state)
{
	state->input = NULL;
	token_free(state->token);
	state->token = NULL;
	state->emited_token = false;
	while (state->input_stack.len > 0)
		input_stack_pop(&state->input_stack);
}
