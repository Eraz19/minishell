/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:47:13 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/05 23:24:37 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "param_braced_.h"
#include "quote_removal_.h"
#include "expander_substitutions_.h"

t_error	parse_braced_op(
			t_expander *expander,
			bool *colon,
			char *op,
			size_t *op_items)
{
	t_word_item	first;
	t_word_item	second;

	word_get(&first, &expander->word, 0);
	*colon = (first.c == ':');
	*op = first.c;
	*op_items = 1;
	if (*colon)
	{
		word_get(&second, &expander->word, 1);
		*op = second.c;
		*op_items = 2;
	}
	else if (braced_op_is_doubled(&expander->word, first.c))
		*op_items = 2;
	if (!is_valid_braced_op(*op))
		return (expander->err = error(ERR_PARAM_BAD_SUBSTITUTION));
	if (*colon && (*op == '#' || *op == '%'))
		return (expander->err = error(ERR_PARAM_BAD_SUBSTITUTION));
	return (expander->err = word_remove(&expander->word, 0, *op_items));
}

t_error	braced_take_operand(
			t_expander *expander,
			size_t operand_len,
			t_word *operand)
{
	size_t		i;
	t_word_item	item;

	word_init(operand);
	i = 0;
	while (i < operand_len)
	{
		word_get(&item, &expander->word, i);
		item.opt.i = i;
		expander->err = word_push(operand, item);
		if (expander->err.type)
			return (word_free(operand), expander->err);
		i++;
	}
	return (expander->err = word_remove(&expander->word, 0, operand_len));
}

t_error	braced_quote_remove_result(t_expander *expander)
{
	expander->word = expander->word_exp;
	word_init(&expander->word_exp);
	while (expander->word.len > 0 && !expander->err.type)
		quote_remove_char(expander);
	return (word_free(&expander->word), expander->err);
}

t_error	expand_operand(t_expander *expander, t_word *operand, t_word *out)
{
	t_word	saved_word;
	t_word	saved_word_exp;
	bool	saved_in_operand;

	saved_word = expander->word;
	saved_word_exp = expander->word_exp;
	saved_in_operand = expander->in_operand;
	expander->word = *operand;
	expander->in_operand = true;
	word_init(&expander->word_exp);
	while (expander->word.len > 0)
	{
		if (substitution_char(expander).type)
			break ;
	}
	word_free(&expander->word);
	braced_quote_remove_result(expander);
	*out = expander->word_exp;
	expander->word = saved_word;
	expander->word_exp = saved_word_exp;
	expander->in_operand = saved_in_operand;
	return (expander->err);
}

t_error	braced_operand_str(
			t_expander *expander,
			t_word *operand,
			t_string *out)
{
	t_word	expanded;

	expander->err = expand_operand(expander, operand, &expanded);
	if (expander->err.type)
		return (word_free(&expanded), expander->err);
	expander->err = to_str(out, &expanded, 0, expanded.len);
	return (word_free(&expanded), expander->err);
}
