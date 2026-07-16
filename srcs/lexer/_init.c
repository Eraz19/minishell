#include "lexer.h"

void	lexer_init(t_lexer *state)
{
	*state = (t_lexer){0};
	lexer_input_stack_init(&state->input_stack);
	context_stack_init(&state->context);
	state->last_index.start = -1;
	state->last_index.end = -1;
	state->last_index.error = -1;
}

void	lexer_free(t_lexer *state)
{
	lexer_input_stack_free(&state->input_stack);
	ft_bzero(state->context.data, state->context.cap);
	vector_free(&state->context, NULL);
	*state = (t_lexer){0};
}

t_error	lexer_push_input(t_lexer *state, t_string *str)
{
	t_lexer_input_stack_item	*item;

	state->err = lexer_input_stack_item_init(&item);
	if (state->err.type)
		return (string_free(str), state->err);
	string_take(&item->str, str->data, str->cap, (ssize_t)str->len);
	string_init(str, 0, NULL, 0);
	state->err = lexer_input_stack_push(&state->input_stack, item);
	if (state->err.type)
		return (lexer_input_stack_item_free(&item), state->err);
	return (state->err);
}

void	lexer_clear(t_lexer *state)
{
	state->input = NULL;
	state->token = NULL;
	state->emited_token = false;
	while (state->input_stack.len > 0)
		lexer_input_stack_pop(&state->input_stack);
	while (state->context.len > 0)
	{
		if (context_stack_bpop(&state->context, NULL).type)
			break ;
	}
	state->last_index.start = -1;
	state->last_index.end = -1;
	state->last_index.error = -1;
}
