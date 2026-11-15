/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_operand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:47:35 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/05 23:25:01 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "param_braced_.h"
#include "expander_substitutions_.h"

static t_error	collect_operand_field(t_expander *expander)
{
	if (expander->err.type)
		return (word_free(&expander->word_exp), expander->err);
	expander->err = fields_push(&expander->fields_exp, expander->word_exp);
	if (expander->err.type)
		word_free(&expander->word_exp);
	return (expander->err);
}

static t_error	operand_to_fields(
					t_expander *expander,
					t_word *operand,
					t_fields *out)
{
	t_word		saved_word;
	t_word		saved_word_exp;
	t_fields	saved_fields_exp;
	bool		saved_in_operand;

	saved_word = expander->word;
	saved_word_exp = expander->word_exp;
	saved_fields_exp = expander->fields_exp;
	saved_in_operand = expander->in_operand;
	expander->word = *operand;
	word_init(&expander->word_exp);
	fields_init(&expander->fields_exp);
	while (expander->word.len > 0 && !expander->err.type)
		substitution_char(expander);
	word_free(&expander->word);
	if (expander->fields_exp.len == 0)
		braced_quote_remove_result(expander);
	collect_operand_field(expander);
	*out = expander->fields_exp;
	expander->word = saved_word;
	expander->word_exp = saved_word_exp;
	expander->fields_exp = saved_fields_exp;
	expander->in_operand = saved_in_operand;
	return (expander->err);
}

static t_error	emit_operand_items(
					t_expander *expander,
					const t_word *field,
					t_word_item_opt opt,
					bool finished)
{
	size_t		i;
	t_word_item	item;

	i = 0;
	while (i < field->len)
	{
		word_get(&item, field, i);
		if (opt.quoted != CONTEXT_NONE)
			item.opt.quoted = opt.quoted;
		item.opt.context = CONTEXT_NONE;
		item.opt.context_len = 0;
		if (finished)
			item.opt.is_expand_res = true;
		expander->err = word_push(&expander->word_exp, item);
		if (expander->err.type)
			return (expander->err);
		i++;
	}
	return (expander->err);
}

static t_error	emit_operand_fields(
					t_expander *expander,
					t_fields *fields,
					t_word_item_opt opt,
					bool finished)
{
	size_t	i;
	t_word	field;

	i = 0;
	while (i < fields->len)
	{
		field = ((t_word *)fields->data)[i];
		if (i != 0)
		{
			expander->err = fields_push(
					&expander->fields_exp,
					expander->word_exp);
			if (expander->err.type)
				return (expander->err);
			word_init(&expander->word_exp);
		}
		expander->err = emit_operand_items(expander, &field, opt, finished);
		if (expander->err.type)
			return (expander->err);
		i++;
	}
	return (expander->err);
}

t_error	braced_use_operand(
			t_expander *expander,
			t_word *operand,
			t_word_item_opt opt)
{
	t_fields	fields;

	expander->err = operand_to_fields(expander, operand, &fields);
	if (expander->err.type)
		return (fields_free(&fields), expander->err);
	expander->err = emit_operand_fields(
			expander, &fields, opt, fields.len <= 1);
	return (fields_free(&fields), expander->err);
}
