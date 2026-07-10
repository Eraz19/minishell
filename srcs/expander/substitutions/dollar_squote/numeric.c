#include "dollar_squote_expansion_.h"

static t_error	octal_convert(t_expander *expander, t_word_item_opt opt)
{
	unsigned int	val;

	if (dollar_squote_read_number(expander, 8, 3, &val).type)
		return (expander->err);
	return (dollar_squote_emit(expander, (char)(val & 0xFF), opt));
}

static t_error	hex_convert(t_expander *expander, t_word_item_opt opt)
{
	unsigned int	val;

	if (dollar_squote_read_number(expander, 16, 2, &val).type)
		return (expander->err);
	return (dollar_squote_emit(expander, (char)(val & 0xFF), opt));
}

t_error	dollar_squote_numeric_escape(t_expander *expander, t_word_item_opt opt)
{
	t_word_item	item;

	expander->err = word_get(&item, &expander->word, 0);
	if (expander->err.type)
		return (expander->err);
	if (item.c >= '0' && item.c <= '7')
		return (octal_convert(expander, opt));
	expander->err = word_remove(&expander->word, 0, 1);
	if (expander->err.type)
		return (expander->err);
	return (hex_convert(expander, opt));
}

t_error	dollar_squote_control_escape(t_expander *expander, t_word_item_opt opt)
{
	t_word_item	item;
	char		c;

	expander->err = word_remove(&expander->word, 0, 1);
	if (expander->err.type)
		return (expander->err);
	if (expander->word.len == 0)
		return (dollar_squote_emit(expander, '\\', opt));
	expander->err = word_get(&item, &expander->word, 0);
	if (expander->err.type)
		return (expander->err);
	c = item.c;
	if (c >= 'a' && c <= 'z')
		c = (char)(c - 32);
	expander->err = word_remove(&expander->word, 0, 1);
	if (expander->err.type)
		return (expander->err);
	return (dollar_squote_emit(expander, (char)(c ^ 0x40), opt));
}
