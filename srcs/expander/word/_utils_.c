#include <stdlib.h>
#include "expander_word_.h"

t_error	expander_word_remove(t_expander_word *word, size_t start, size_t len)
{
	size_t					i;
	t_expander_word_item	item;

	i = 0;
	while (i < len)
	{
		if (word->len <= start + i)
			return (error(ERR_NO));
		if (!vector_remove(word, start, &item))
			return (error(ERR_NO));
		i++;
	}
	return (error(ERR_NO));
}

t_error	expander_word_to_str(
	t_expander_word *word,
	char **str,
	size_t start,
	size_t len)
{
	size_t					i;
	t_error					err;
	t_expander_word_item	item;

	*str = malloc(sizeof(char) * (len + 1));
	if (*str == NULL)
		return (error_sys());
	i = 0;
	while (i < len)
	{
		if (word->len <= start + i)
			return (free(*str), error(ERR_INDEX_OUT_OF_BOUND));
		err = expander_word_get(word, start + i, &item);
		if (err.type)
			return (free(*str), err);
		(*str)[i++] = item.c;
	}
	return ((*str)[i] = '\0', error(ERR_NO));
}

t_error	expander_word_from_str(
	t_expander_word *word,
	const char *str,
	t_expander_word_item_opt opt)
{
	size_t					i;
	t_error					err;
	t_expander_word_item	item;

	i = 0;
	while (str[i] != '\0')
	{
		item = expander_word_item_init(
			str[i],
			opt.quoted,
			opt.context,
			opt.is_expand_res);
		err = expander_word_push(word, item);
		if (err.type)
			return (err);
		i++;
	}
	return (error(ERR_NO));
}
