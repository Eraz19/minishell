#include "expander_loader_.h"

void	expander_loader_init(t_expander_loader *state)
{
	*state = (t_expander_loader){0};
	context_stack_init(&state->stack);
	expander_word_init(&state->loaded_word);
	context_stack_init(&state->loading_stack);
}

void	expander_loader_free(t_expander_loader *state)
{
	context_stack_free(&state->stack);
	expander_word_free(&state->loaded_word);
	context_stack_free(&state->loading_stack);
	if (state->context_item)
		state->context_item = NULL;
	*state = (t_expander_loader){0};
}

t_error	expander_loader_load(
			t_expander_loader *state,
			const t_context_stack *stack,
			t_string *word)
{
	if (!string_dup(&state->word, word))
		return (state->err = error_sys());
	if (stack == NULL)
		return (state->err);
	return (state->err = context_stack_dup(&state->stack, stack));
}
