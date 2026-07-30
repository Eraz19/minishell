#include "dollar_squote_expansion_.h"

t_word_item_opt	dollar_squote_result_opt(t_word_item_opt in)
{
	in.context = CONTEXT_NONE;
	in.escaped = false;
	in.is_expand_res = true;
	return (in);
}

t_error	dollar_squote_emit(t_expander *expander, char c, t_word_item_opt opt)
{
	t_word_item	item;

	if (c == '\0')
		return (error(ERR_NO));
	item = word_item_init(c, opt);
	return (expander->err = word_push(&expander->word_exp, item));
}

int	dollar_squote_digit(char c, int base)
{
	int	value;

	if (c >= '0' && c <= '9')
		value = c - '0';
	else if (c >= 'a' && c <= 'f')
		value = c - 'a' + 10;
	else if (c >= 'A' && c <= 'F')
		value = c - 'A' + 10;
	else
		return (-1);
	if (value >= base)
		return (-1);
	return (value);
}

t_error	dollar_squote_read_number(
	t_expander *expander,
	int base,
	size_t max,
	uint *value)
{
	size_t		n;
	t_word_item	item;
	int			digit;

	n = 0;
	*value = 0;
	while (n < max && expander->word.len > 0)
	{
		expander->err = word_get(&item, &expander->word, 0);
		if (expander->err.type)
			return (expander->err);
		digit = dollar_squote_digit(item.c, base);
		if (digit < 0)
			break ;
		*value = *value * (unsigned int)base + (unsigned int)digit;
		expander->err = word_remove(&expander->word, 0, 1);
		if (expander->err.type)
			return (expander->err);
		n++;
	}
	return (error(ERR_NO));
}
