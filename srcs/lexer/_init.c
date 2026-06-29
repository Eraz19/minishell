#include <stdlib.h>
#include "lexer.h"

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

t_error	lexer_push_input(t_lexer *state, char *str)
{
	t_input_lexer_stack_item	*item;

	state->err = input_parser_stack_item_init(&item);
	if (state->err.type)
		return (free(str), state->err);
	item->str = str;
	state->err = input_stack_push(&state->input_stack, item);
	if (state->err.type)
		return (input_parser_stack_item_free(&item), state->err);
	return (state->err);
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
