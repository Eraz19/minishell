#include <stdlib.h>
#include "expander_.h"
#include "expander_loader_.h"

void	expander_init(t_expander *state, t_expander_role role)
{
	*state = (t_expander){0};
	state->role = role;
	expander_fields_init(&state->fields);
	expander_word_init(&state->word_exp);
	expander_fields_init(&state->fields_exp);
}

void	expander_free(t_expander *state)
{
	expander_fields_free(&state->fields);
	expander_word_free(&state->word_exp);
	expander_fields_free(&state->fields_exp);
	*state = (t_expander){0};
}

t_error	expander_load(t_expander *state, t_expander_args *args)
{
	size_t				word_len;
	t_expander_word		word_copy;
	t_expander_loader	loader_state;

	state->assignement_offset = args->assignment_offset;
	expander_loader_init(&loader_state);
	state->err = expander_loader_load(&loader_state, args->contexts, args->value);
	if (state->err.type)
		return (expander_loader_free(&loader_state), state->err);
	word_len = str_len(loader_state.word);
	while (loader_state.i < word_len)
	{
		state->err = expander_loader_build(&loader_state);
		if (state->err.type)
			return (expander_loader_free(&loader_state), state->err);
	}
	state->err = expander_word_dup(&word_copy, &loader_state.loaded_word);
	if (state->err.type)
	{
		expander_loader_free(&loader_state);
		return (expander_word_free(&word_copy), state->err);
	}
	state->err = expander_fields_push(&state->fields, word_copy);
	return (expander_loader_free(&loader_state), state->err);
}
