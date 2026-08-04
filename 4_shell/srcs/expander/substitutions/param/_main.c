/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:47:47 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 17:47:48 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "param_braced_.h"
#include "param_unbraced_.h"

t_error	param_expansion(t_expander *expander)
{
	t_word_item	item;

	expander->err = word_get(&item, &expander->word, 1);
	if (expander->err.type)
		return (expander->err);
	if (item.c == '{')
		return (expand_braced(expander));
	else
		return (expand_unbraced(expander));
}

bool	is_valid_param(t_word_item *item)
{
	if (item->c == '?'
		|| item->c == '#'
		|| item->c == '-'
		|| item->c == '*'
		|| item->c == '$'
		|| item->c == '!'
		|| item->c == '@'
		|| item->c == '_'
		|| ft_isalnum(item->c))
		return (true);
	return (false);
}

bool	context_prevent_param_expansion(t_word_item *item)
{
	t_context	context;
	bool		is_valid_quoting;
	bool		is_valid_context;

	context = item->opt.context;
	is_valid_context = context == CONTEXT_NONE || context == CONTEXT_PARAM;
	is_valid_quoting = item->opt.quoted != CONTEXT_SQUOTE && !item->opt.escaped;
	return (!is_valid_context || !is_valid_quoting);
}

bool	is_param_expansion(t_expander *expander, t_word_item *current_item)
{
	t_error		err;
	t_word_item	item;

	if (!flag_is_active((uint)expander->flags, EXP_PARAM))
		return (false);
	if (current_item->c != '$' || context_prevent_param_expansion(current_item))
		return (false);
	err = word_get(&item, &expander->word, 1);
	if (err.type)
		return (false);
	if (item.c == '{')
		return (true);
	return (is_valid_param(&item));
}
