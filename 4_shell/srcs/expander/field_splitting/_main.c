/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:43:44 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 17:43:45 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "field_splitting_.h"

static t_error	field_splitting_char(t_expander *expander)
{
	t_word_item	item;

	expander->err = word_get(&item, &expander->word, 0);
	if (expander->err.type)
		return (expander->err);
	if (!is_delim(item, &expander->ifs))
		return (consume_word_item(expander, item));
	if (is_it_white_space_ifs(item.c))
		return (fields_splitting_on_ifs_white_space(expander));
	return (fields_splitting_on_ifs_non_white_space(expander));
}

static t_error	field_splitting_word(t_expander *expander)
{
	expander->err = fields_fpop(&expander->word, &expander->fields);
	if (expander->err.type)
		return (expander->err);
	word_init(&expander->word_exp);
	while (expander->word.len > 0)
	{
		if (field_splitting_char(expander).type)
			return (expander->err);
	}
	word_free(&expander->word);
	if (expander->word_exp.len > 0)
		return (delim_field(expander));
	return (expander->err);
}

t_error	field_splitting(t_expander *expander)
{
	fields_init(&expander->fields_exp);
	while (expander->fields.len > 0)
	{
		if (field_splitting_word(expander).type)
			return (fields_free(&expander->fields_exp), expander->err);
	}
	fields_free(&expander->fields);
	expander->fields = expander->fields_exp;
	fields_init(&expander->fields_exp);
	return (expander->err);
}
