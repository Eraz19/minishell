/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   positional_.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:15:43 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/06 14:19:49 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "param_braced_.h"
#include "param_expansion_.h"

static t_error	braced_positional_error(
					t_expander *expander,
					t_positional_exp *positional_exp)
{
	t_string	name;
	char		symbol[2];

	symbol[0] = positional_exp->symbol;
	symbol[1] = '\0';
	if (!string_init(&name, 0, symbol, -1))
	{
		expander->err = error_sys();
		return (word_free(&positional_exp->operand_word), expander->err);
	}
	expander->err = braced_error(
			expander,
			&name,
			&positional_exp->operand_word);
	return (string_free(&name), expander->err);
}

static t_error	emit_stripped(
					t_expander *expander,
					t_string *stripped,
					t_positional_exp *positional_exp,
					size_t i)
{
	t_word	word_exp;

	expander->err = from_str(&word_exp, stripped, positional_exp->result_opt);
	if (expander->err.type)
		return (string_free(stripped), expander->err);
	if (positional_exp->symbol == '@' && !expander->in_operand)
		expander->err = append_param_as_field(expander, word_exp,
				positional_exp->result_opt, i);
	else
	{
		if (i != 0 && expander->ifs.len > 0)
			expander->err = word_push(&expander->word_exp, word_item_init(
						expander->ifs.data[0], positional_exp->result_opt));
		if (!expander->err.type && !vector_merge(&expander->word_exp,
				&word_exp, expander->word_exp.len))
			expander->err = error_sys();
	}
	word_free(&word_exp);
	return (string_free(stripped), expander->err);
}

t_error	braced_positional_remove(
			t_expander *expander,
			t_positional_exp *positional_exp,
			bool largst)
{
	size_t				i;
	t_string			strip;
	t_string			param;
	const t_positionals	*params;
	t_string			pattern;

	expander->err = braced_build_pattern(expander,
			&positional_exp->operand_word, &pattern);
	if (expander->err.type)
		return (expander->err);
	expander->err = env_get_positionals(&params);
	i = 0;
	while (!expander->err.type && i < params->len)
	{
		param = ((t_string *)params->data)[i];
		if (positional_exp->op_char == '#')
			expander->err = remove_prefix(&param, pattern.data, largst, &strip);
		else
			expander->err = remove_suffix(&param, pattern.data, largst, &strip);
		if (!expander->err.type)
			emit_stripped(expander, &strip, positional_exp, i);
		i++;
	}
	return (string_free(&pattern), expander->err);
}

bool	positionals_all_empty(const t_positionals *params)
{
	size_t	i;

	i = 0;
	while (i < params->len)
	{
		if (((t_string *)params->data)[i].len > 0)
			return (false);
		i++;
	}
	return (true);
}

t_error	braced_positional_apply(
			t_expander *expander,
			t_positional_exp *positional_exp)
{
	if (positional_exp->op_char == '=')
	{
		word_free(&positional_exp->operand_word);
		return (expander->err = error(ERR_VAR_INVALID_NAME));
	}
	if (positional_exp->op_char == '+')
	{
		if (positional_exp->is_triggered)
			return (word_free(&positional_exp->operand_word), expander->err);
		return (braced_use_operand(expander,
				&positional_exp->operand_word,
				positional_exp->result_opt));
	}
	if (!positional_exp->is_triggered)
		return (word_free(&positional_exp->operand_word),
			emit_positionals(
				expander,
				positional_exp->symbol,
				positional_exp->result_opt));
	if (positional_exp->op_char == '-')
		return (braced_use_operand(
				expander,
				&positional_exp->operand_word,
				positional_exp->result_opt));
	return (braced_positional_error(expander, positional_exp));
}
