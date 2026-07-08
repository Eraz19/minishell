#include <stdint.h>
#include "dollar_squote_expansion_.h"

bool	dollar_squote_build_map(t_hashmap *escapes)
{
	if (!hashmap_init(escapes, 16, NULL))
		return (false);
	if (!hashmap_put(escapes, "a", (void *)(intptr_t)7)
		|| !hashmap_put(escapes, "b", (void *)(intptr_t)8)
		|| !hashmap_put(escapes, "e", (void *)(intptr_t)27)
		|| !hashmap_put(escapes, "f", (void *)(intptr_t)12)
		|| !hashmap_put(escapes, "n", (void *)(intptr_t)10)
		|| !hashmap_put(escapes, "r", (void *)(intptr_t)13)
		|| !hashmap_put(escapes, "t", (void *)(intptr_t)9)
		|| !hashmap_put(escapes, "v", (void *)(intptr_t)11)
		|| !hashmap_put(escapes, "\\", (void *)(intptr_t)92)
		|| !hashmap_put(escapes, "'", (void *)(intptr_t)39)
		|| !hashmap_put(escapes, "\"", (void *)(intptr_t)34))
		return (hashmap_free(escapes), false);
	return (true);
}

static bool	dollar_squote_simple_escape(char c, char *out, t_hashmap *escapes)
{
	char	key[2];
	const char	*value;

	key[0] = c;
	key[1] = '\0';
	value = hashmap_get(escapes, key);
	if (value == NULL)
		return (false);
	*out = (char)(intptr_t)value;
	return (true);
}

static bool	dollar_squote_is_numeric(char c)
{
	return (c == 'x' || (c >= '0' && c <= '7'));
}

static t_error	dollar_squote_simple_apply(
	t_expander *expander,
	char c,
	t_word_item_opt opt,
	t_hashmap *escapes)
{
	char	byte;

	if (dollar_squote_simple_escape(c, &byte, escapes))
	{
		if (word_remove(&expander->word, 0, 1).type)
			return (expander->err);
		return (dollar_squote_emit(expander, byte, opt));
	}
	if (dollar_squote_emit(expander, '\\', opt).type)
		return (expander->err);
	if (dollar_squote_emit(expander, c, opt).type)
		return (expander->err);
	return (word_remove(&expander->word, 0, 1));
}

t_error	dollar_squote_escape(
	t_expander *expander,
	t_word_item_opt opt,
	t_hashmap *escapes)
{
	t_word_item	item;

	if (word_remove(&expander->word, 0, 1).type)
		return (expander->err);
	if (expander->word.len == 0)
		return (dollar_squote_emit(expander, '\\', opt));
	expander->err = word_get(&item, &expander->word, 0);
	if (expander->err.type)
		return (expander->err);
	if (item.c == 'c')
		return (dollar_squote_control_escape(expander, opt));
	if (dollar_squote_is_numeric(item.c))
		return (dollar_squote_numeric_escape(expander, opt));
	return (dollar_squote_simple_apply(expander, item.c, opt, escapes));
}
