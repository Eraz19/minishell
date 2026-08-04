/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:46:39 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 17:46:40 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dollar_squote_expansion_.h"

bool	is_dollar_squote_expansion(t_word_item *current_item, uint flags)
{
	if (!flag_is_active(flags, EXP_DOLLAR_SQUOTE))
		return (false);
	if (current_item->opt.quoted == CONTEXT_DOLLAR_SQUOTE)
		return (true);
	return (false);
}

static t_error	dollar_squote_strip_opening(t_expander *expander)
{
	t_word_item	item;

	expander->err = word_get(&item, &expander->word, 0);
	if (expander->err.type)
		return (expander->err);
	if (item.c == '$' && !item.opt.escaped)
	{
		expander->err = word_remove(&expander->word, 0, 1);
		if (expander->err.type)
			return (expander->err);
		expander->err = word_get(&item, &expander->word, 0);
		if (expander->err.type)
			return (expander->err);
	}
	if (item.c == '\'' && !item.opt.escaped)
		return (expander->err = word_remove(&expander->word, 0, 1));
	return (expander->err);
}

static t_error	dollar_squote_next(
	t_expander *expander,
	t_word_item_opt opt,
	t_hashmap *escapes)
{
	t_word_item	item;

	expander->err = word_get(&item, &expander->word, 0);
	if (expander->err.type)
		return (expander->err);
	if (item.c == '\\' && !item.opt.escaped)
		return (dollar_squote_escape(expander, opt, escapes));
	if (dollar_squote_emit(expander, item.c, opt).type)
		return (expander->err);
	return (expander->err = word_remove(&expander->word, 0, 1));
}

static t_error	dollar_squote_body(
	t_expander *expander,
	t_word_item_opt opt,
	t_hashmap *escapes)
{
	t_word_item	item;

	while (expander->word.len > 0)
	{
		expander->err = word_get(&item, &expander->word, 0);
		if (expander->err.type)
			return (expander->err);
		if (item.opt.quoted != CONTEXT_DOLLAR_SQUOTE)
			break ;
		if (item.c == '\'' && !item.opt.escaped)
			return (expander->err = word_remove(&expander->word, 0, 1));
		if (dollar_squote_next(expander, opt, escapes).type)
			return (expander->err);
	}
	return (expander->err);
}

t_error	dollar_squote_expansion(t_expander *expander)
{
	t_word_item		item;
	t_word_item_opt	opt;
	t_hashmap		escapes;

	expander->err = word_get(&item, &expander->word, 0);
	if (expander->err.type)
		return (expander->err);
	opt = dollar_squote_result_opt(item.opt);
	if (dollar_squote_strip_opening(expander).type)
		return (expander->err);
	if (!dollar_squote_build_map(&escapes))
		return (expander->err = error_sys());
	dollar_squote_body(expander, opt, &escapes);
	return (hashmap_free(&escapes), expander->err);
}
