/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:46:24 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 18:42:22 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_sub.h"
#include "backtick_substitution_.h"

bool	is_backtick_substitution(t_word_item *current_item, uint flags)
{
	if (!flag_is_active((uint)flags, EXP_CMD_SUB))
		return (false);
	if (current_item->opt.context == CONTEXT_BACKTICK)
		return (true);
	return (false);
}

static bool	is_removable_escape(char c)
{
	return (c == '$' || c == '`' || c == '\\');
}

static t_error	extract_backtick_cmd(
					t_string *out,
					const t_word *word,
					size_t len)
{
	size_t		i;
	t_word_item	item;
	t_word_item	next;

	if (!string_init(out, 0, "", -1))
		return (error_sys());
	i = 1;
	while (i <= len)
	{
		word_get(&item, word, i++);
		if (item.c == '\\' && i <= len)
		{
			word_get(&next, word, i);
			if (is_removable_escape(next.c))
			{
				item = next;
				i++;
			}
		}
		if (!string_append_n(out, &item.c, 1))
			return (string_free(out), error_sys());
	}
	return (error(ERR_NO));
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

t_error	backtick_substitution(t_expander *expander)
{
	t_word_item	item;
	t_string	cmd_res;
	t_string	cmd_str;

	word_get(&item, &expander->word, 0);
	expander->err = extract_backtick_cmd(
			&cmd_str,
			&expander->word,
			item.opt.context_len - 2);
	if (expander->err.type)
		return (expander->err);
	expander->err = cmd_sub_run_string(
			&cmd_str,
			&cmd_res,
			expander->exit_status);
	if (expander->err.type)
		return (string_free(&cmd_str), string_free(&cmd_res),
			expander->err);
	string_free(&cmd_str);
	merge_cmd_res_into_word_exp(expander, &item.opt, &cmd_res);
	return (string_free(&cmd_res), expander->err);
}
