#include "expander_word_.h"

t_error	expander_word_push(t_expander_word *word, t_expander_word_item item)
{
	if (!vector_push(word, &item))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	expander_word_pop(t_expander_word *word, t_expander_word_item *item)
{
	if (word->len == 0)
		return (error(ERR_EMPTY_STACK));
	if (!vector_remove(word, 0, item))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	expander_word_dup(t_expander_word *dst, t_expander_word *src)
{
	if (!vector_dup(dst, src))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	expander_word_peek(
			t_expander_word *word,
			t_expander_word_item *item,
			size_t i)
{
	if (word->len == 0)
		return (error(ERR_EMPTY_STACK));
	else if (i >= word->len)
		return (error(ERR_INDEX_OUT_OF_BOUND));
	return (*item = ((t_expander_word_item *)word->data)[i], error(ERR_NO));
}

t_error	expander_word_get(
			t_expander_word *word,
			size_t index,
			t_expander_word_item *item)
{
	if (word->len == 0)
		return (error(ERR_EMPTY_STACK));
	else if (index >= word->len)
		return (error(ERR_INDEX_OUT_OF_BOUND));
	return (*item = ((t_expander_word_item *)word->data)[index], error(ERR_NO));
}
