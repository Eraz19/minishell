#include "quote_removal_.h"
#include "quote_removal_context_.h"

t_error	quote_removal_quoted(
	t_expander *state,
	t_expander_word_item item,
	t_expander_word *word,
	t_expander_word *word_expanded)
{
	if (item.opt.quoted == CONTEXT_SQUOTE)
		context_squote(state, word, word_expanded);
	else if (item.opt.quoted == CONTEXT_DQUOTE)
		context_dquote(state, word, word_expanded);
	else if (item.opt.quoted == CONTEXT_HEREDOC)
		context_heredoc(state, item, word, word_expanded);
	else if (item.opt.quoted == CONTEXT_DOLLAR_SQUOTE)
	{
		state->err = expander_word_pop(word, &item);
		if (state->err.type)
			return (state->err);
		context_dollar_squote(state, word, word_expanded);
	}
	return (state->err);
}

t_error	quote_remove_char(
	t_expander *state,
	t_expander_word *word,
	t_expander_word *word_exp)
{
	t_expander_word_item	item;

	state->err = expander_word_pop(word, &item);
	if (state->err.type)
		return (state->err);
	if (item.opt.is_expand_res)
		state->err = expander_word_push(word_exp, item);
	else if (item.opt.quoted == CONTEXT_NONE)
	{
		if (item.c != '\\')
			state->err = expander_word_push(word_exp, item);
		else
		{
			if (word->len == 0)
				return (state->err = error(ERR_NO));
			state->err = expander_word_pop(word, &item);
			if (state->err.type)
				return (state->err);
			state->err = expander_word_push(word_exp, item);
		}
	}
	else
		quote_removal_quoted(state, item, word, word_exp);
	return (state->err);
}

t_error	quote_removal_word(t_expander *state, t_expander_fields *fields)
{
	t_expander_word	word;
	t_expander_word	word_exp;

	state->err = expander_fields_pop(&state->fields, &word);
	if (state->err.type)
		return (state->err);
	expander_word_init(&word_exp);
	while (word.len > 0)
	{
		if (quote_remove_char(state, &word, &word_exp).type)
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

t_error	quote_removal(t_expander *state)
{
	t_expander_fields	fields;

	expander_fields_init(&fields);
	while (state->fields.len > 0)
	{
		if (quote_removal_word(state, &fields).type)
			return (expander_fields_free(&fields), state->err);
	}
	expander_fields_free(&state->fields);
	state->fields = fields;
	return (state->err);
}
