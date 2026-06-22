#include <stdlib.h>
#include "expander_loader_.h"

t_error	expander_loader_build(t_expander_loader *state)
{
	state->quoting = CONTEXT_NONE;
	if (is_substitution_start(state))
		expander_loader_substitution(state);
	else if (is_char_escaped(state))
		expander_loader_consume(state, 2);
	else if (is_quoting_context(state->word + state->i, &state->quoting))
		expander_loader_quoted(state);
	else
		expander_loader_consume(state, 1);
	return (state->err);
}

static t_error	expander_loader_word_extract(t_expander_word word, char **str)
{
	size_t					i;
	t_error					err;
	t_expander_word_item	item;

	i = 0;
	*str = malloc(sizeof(char) * (word.len + 1));
	if (*str == NULL)
		return (error_sys());
	while (word.len > 0)
	{
		err = expander_word_pop(&word, &item);
		if (err.type)
			return (free(*str), *str = NULL, err);
		if (item.c == '\0' && word.len > 0)
			continue ;
		(*str)[i++] = item.c;
	}
	return ((*str)[i] = '\0', error(ERR_NO));
}

t_error	expander_loader_extract(t_expander_fields *fields, char ***words)
{
	size_t			i;
	t_error			err;
	t_expander_word	word;
	char 			*str;

	i = 0;
	*words = malloc(sizeof(char *) * (fields->len + 1));
	if (!*words)
		return (error_sys());
	ft_bzero(*words, sizeof(char *) * (fields->len + 1));
	while (fields->len > 0)
	{
		err = expander_fields_pop(fields, &word);
		if (err.type)
			return (str_array_free(words), err);
		err = expander_loader_word_extract(word, &str);
		if (err.type)
			return (str_array_free(words), expander_word_free(&word), err);
		(*words)[i++] = str;
		expander_word_free(&word);
	}
	return (error(ERR_NO));
}
