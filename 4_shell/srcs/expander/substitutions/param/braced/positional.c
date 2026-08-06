/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   positional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:47:25 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/06 14:20:47 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "param_braced_.h"
#include "param_expansion_.h"

static t_error	braced_positional_bare(
					t_expander *expander,
					t_positional_exp *positional_exp)
{
	expander->err = emit_positionals(
			expander,
			positional_exp->symbol,
			positional_exp->result_opt);
	if (expander->err.type)
		return (expander->err);
	if (braced_expect_close(expander).type)
		return (expander->err);
	return (expander->err = word_remove(&expander->word, 0, 1));
}

static t_error	braced_positional_op(
					t_expander *expander,
					t_positional_exp *positional_exp,
					size_t body_len)
{
	bool				colon;
	size_t				op_items;
	const t_positionals	*params;

	expander->err = parse_braced_op(expander, &colon, &positional_exp->op_char,
			&op_items);
	if (expander->err.type)
		return (expander->err);
	expander->err = braced_take_operand(expander, body_len - 1 - op_items,
			&positional_exp->operand_word);
	if (expander->err.type)
		return (expander->err);
	if (braced_expect_close(expander).type
		|| word_remove(&expander->word, 0, 1).type)
		return (word_free(&positional_exp->operand_word), expander->err);
	expander->err = env_get_positionals(&params);
	if (expander->err.type)
		return (word_free(&positional_exp->operand_word), expander->err);
	if (positional_exp->op_char == '#' || positional_exp->op_char == '%')
		return (braced_positional_remove(expander, positional_exp,
				op_items == 2));
	positional_exp->is_triggered = (params->len == 0)
		|| (colon && positionals_all_empty(params)
			&& (params->len <= 1 || expander->ifs.len == 0));
	return (braced_positional_apply(expander, positional_exp));
}

t_error	expand_braced_positional(
			t_expander *expander,
			size_t body_len,
			t_word_item_opt origin)
{
	t_positional_exp	positional_exp;
	t_word_item			item;

	word_get(&item, &expander->word, 0);
	positional_exp.symbol = item.c;
	positional_exp.result_opt = origin;
	positional_exp.result_opt.is_expand_res = true;
	expander->err = word_remove(&expander->word, 0, 1);
	if (expander->err.type)
		return (expander->err);
	if (body_len == 1)
		return (braced_positional_bare(expander, &positional_exp));
	return (braced_positional_op(expander, &positional_exp, body_len));
}
