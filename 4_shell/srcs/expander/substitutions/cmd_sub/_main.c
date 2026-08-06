/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:46:31 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 18:44:09 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_sub.h"
#include "cmd_substitution_.h"

bool	is_cmd_substitution(t_word_item *current_item, uint flags)
{
	if (!flag_is_active((uint)flags, EXP_CMD_SUB))
		return (false);
	if (current_item->opt.context == CONTEXT_CMD_SUB)
		return (true);
	return (false);
}

static t_error	merge_cmd_res_into_word_exp(
			t_expander *expander,
			t_word_item_opt *item_opt,
			t_string *cmd_res)
{
	t_word	word;
	size_t	span;

	span = item_opt->context_len;
	item_opt->is_expand_res = true;
	item_opt->context = CONTEXT_NONE;
	item_opt->context_len = 0;
	expander->err = from_str(&word, cmd_res, *item_opt);
	if (expander->err.type)
		return (expander->err);
	while (word.len > 0)
	{
		expander->err = forward_word_item(&expander->word_exp, &word);
		if (expander->err.type)
			return (word_free(&word), expander->err);
	}
	expander->err = word_remove(&expander->word, 0, span);
	return (word_free(&word), expander->err);
}

t_error	cmd_substitution(t_expander *expander)
{
	t_word_item	item;
	t_string	cmd_res;

	word_get(&item, &expander->word, 0);
	if (item.opt.context_len == 3)
		return (expander->err = word_remove(&expander->word, 0, 3));
	expander->err = cmd_sub_run_ast(
			expander->ast_vec,
			expander->ast_i,
			&cmd_res,
			expander->exit_status);
	if (expander->err.type)
		return (string_free(&cmd_res), expander->err);
	++expander->ast_i;
	merge_cmd_res_into_word_exp(expander, &item.opt, &cmd_res);
	return (string_free(&cmd_res), expander->err);
}
