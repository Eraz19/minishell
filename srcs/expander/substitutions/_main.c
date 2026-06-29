#include "tilde_expansion_.h"
#include "cmd_substitution_.h"
#include "arith_substitution_.h"
#include "expander_substitutions_.h"
#include "backtick_substitution_.h"
#include "dollar_squote_expansion_.h"
#include "param_expansion_.h"

t_error	substitution_char(
	t_expander *state,
	t_expander_word *word,
	t_expander_word *word_exp)
{
	t_expander_word_item	item;

	state->err = expander_word_pop(word, &item);
	if (state->err.type)
		return (state->err);
	if (is_tilde_expansion(state, word, &item))
	{
		if (item.c == '=' || item.c == ':')
			state->err = expander_word_push(word_exp, item);
		tilde_expansion(state, word, word_exp);
	}
	else if (is_dollar_squote_expansion(&item))
		dollar_squote_expansion(state, word, word_exp);
	else if (is_param_expansion(state, word, &item))
		param_expansion(state, word, word_exp);
	else if (is_cmd_substitution(&item))
		cmd_substitution(state, word, word_exp);
	else if (is_backtick_substitution(&item))
		backtick_substitution(state, word, word_exp);
	else if (is_arith_substitution(&item))
		arith_substitution(state, word, word_exp);
	else
		state->err = expander_word_push(word_exp, item);
	return (state->err);
}

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
		if (substitution_char(state, &word, &word_exp).type)
		{
			expander_word_free(&word);
			expander_word_free(&word_exp);
			return (state->err);
		}
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
