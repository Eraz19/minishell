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

void	lexer_load(t_lexer *state, bool is_stdin)
{
	state->is_stdin = is_stdin;
}
