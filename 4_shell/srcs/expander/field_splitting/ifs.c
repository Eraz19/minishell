#include "field_splitting_.h"

bool	is_it_white_space_ifs(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static t_error	exhaust_ifs_white_space(t_expander *expander)
{
	t_word_item	item;

	while (expander->word.len > 0)
	{
		expander->err = word_get(&item, &expander->word, 0);
		if (expander->err.type)
			return (expander->err);
		if (is_delim(item, &expander->ifs) && is_it_white_space_ifs(item.c))
		{
			expander->err = word_fpop(&item, &expander->word);
			if (expander->err.type)
				return (expander->err);
		}
		else
			break ;
	}
	return (expander->err);
}

t_error	fields_splitting_on_ifs_white_space(t_expander *expander)
{
	t_word_item	item;

	expander->err = exhaust_ifs_white_space(expander);
	if (expander->err.type)
		return (expander->err);
	if (expander->word.len != 0 && expander->word_exp.len != 0)
	{
		expander->err = word_get(&item, &expander->word, 0);
		if (expander->err.type)
			return (expander->err);
		if (!is_delim(item, &expander->ifs))
			return (delim_field(expander));
	}
	return (expander->err);
}

t_error	fields_splitting_on_ifs_non_white_space(t_expander *expander)
{
	t_word_item	item;

	if (delim_field(expander).type)
		return (expander->err);
	expander->err = word_fpop(&item, &expander->word);
	if (expander->err.type)
		return (expander->err);
	if (fields_splitting_on_ifs_white_space(expander).type)
		return (expander->err);
	return (expander->err);
}
