#include "expander_loader_.h"
#include "expander_expansion_.h"

t_error	expander_loader_build(t_expander_loader *state)
{
	state->quoting = CONTEXT_NONE;
	if (is_substitution_start(state))
		expander_loader_substitution(state);
	else if (is_char_escaped(state))
	{
		expander_loader_consume(state, 1, false);
		expander_loader_consume(state, 1, true);
	}
	else if (is_quoting_start(state))
		expander_loader_quoted(state);
	else
		expander_loader_consume(state, 1, false);
	return (state->err);
}

static t_error	expander_loader_word_extract(
					t_expander_word word,
					t_string *str)
{
	t_error					err;
	t_expander_word_item	item;

	if (!string_init(str, 1, NULL, 0))
		return (error_sys());
	while (word.len > 0)
	{
		err = expander_word_pop(&word, &item);
		if (err.type)
			return (string_free(str), err);
		if (item.c == '\0' && word.len > 0)
			continue ;
		if (!string_append_n(str, &item.c, 1))
			return (string_free(str), error_sys());
	}
	return (error(ERR_NO));
}

t_error	expander_loader_extract(t_expander_fields *fields, t_expansion *out)
{
	t_error			err;
	t_expander_word	word;
	t_string		str;

	expansion_init(out);
	while (fields->len > 0)
	{
		err = expander_fields_pop(fields, &word);
		if (err.type)
			return (expansion_free(out), err);
		err = expander_loader_word_extract(word, &str);
		expander_word_free(&word);
		if (err.type)
			return (expansion_free(out), err);
		err = expansion_push(out, &str);
		if (err.type)
			return (string_free(&str), expansion_free(out), err);
	}
	return (error(ERR_NO));
}
