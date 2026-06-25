#include "tilde_expansion_.h"
#include "expander_substitutions.h"

t_error	substitution_word(t_expander *state, t_expander_fields *fields)
{
	t_expander_word	word;
	t_expander_word	word_exp;

	state->err = expander_fields_pop(&state->fields, &word);
	if (state->err.type)
		return (state->err);
	expander_word_init(&word_exp);
	while (word.len > 0)
	{
		if (is_tilde_expansion(state, &state->word) && tilde_expansion(state).type)
			return (state->err);
	}
	expander_word_free(&word);
	state->err = expander_fields_push(fields, word_exp);
	if (state->err.type)
		expander_word_free(&word_exp);
	return (state->err);
}

t_error	substitutions(t_expander *state)
{
	t_expander_fields	fields;

	expander_fields_init(&fields);
	while (state->fields.len > 0)
	{
		if (substitution_word(state, &fields).type)
			return (expander_fields_free(&fields), state->err);
	}
	expander_fields_free(&state->fields);
	state->fields = fields;
	return (state->err);
}
