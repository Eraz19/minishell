/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numeric.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:46:53 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/06 15:56:16 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	t_word_item	next;
	bool		has_digit;

	word_get(&item, &expander->word, 0);
	if (item.c >= '0' && item.c <= '7')
		return (octal_convert(expander, opt));
	has_digit = false;
	if (expander->word.len > 1)
	{
		word_get(&next, &expander->word, 1);
		has_digit = (dollar_squote_digit(next.c, 16) >= 0);
	}
	if (!has_digit)
	{
		if (dollar_squote_emit(expander, '\\', opt).type
			|| dollar_squote_emit(expander, 'x', opt).type)
			return (expander->err);
		return (expander->err = word_remove(&expander->word, 0, 1));
	}
	expander->err = word_remove(&expander->word, 0, 1);
	if (expander->err.type)
		return (expander->err);
	return (hex_convert(expander, opt));
}

static t_error	control_convert(
					t_expander *expander,
					t_word_item item,
					t_word_item_opt opt)
{
	char		c;
	t_word_item	next;

	c = item.c;
	if (c >= 'a' && c <= 'z')
		c = (char)(c - 32);
	expander->err = word_remove(&expander->word, 0, 1);
	if (expander->err.type)
		return (expander->err);
	if (item.c == '\\' && expander->word.len > 0)
	{
		word_get(&next, &expander->word, 0);
		if (next.c == '\\' && next.opt.escaped
			&& !word_remove(&expander->word, 0, 1).type)
			return (dollar_squote_emit(expander, (char)(c ^ 0x40), opt));
	}
	return (dollar_squote_emit(expander, (char)(c ^ 0x40), opt));
}

t_error	dollar_squote_control_escape(t_expander *expander, t_word_item_opt opt)
{
	t_word_item	item;

	expander->err = word_remove(&expander->word, 0, 1);
	if (expander->err.type)
		return (expander->err);
	if (expander->word.len == 0)
		return (dollar_squote_emit(expander, '\\', opt));
	word_get(&item, &expander->word, 0);
	if (item.c == '\'' && !item.opt.escaped)
	{
		if (dollar_squote_emit(expander, '\\', opt).type)
			return (expander->err);
		return (dollar_squote_emit(expander, 'c', opt));
	}
	return (control_convert(expander, item, opt));
}
