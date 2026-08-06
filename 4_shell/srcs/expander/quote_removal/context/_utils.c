/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:45:48 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/05 23:19:43 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h> // DEBUG
#include "quote_removal_context_.h"

static t_error	context_escape(
	t_expander *expander,
	t_context_args args,
	t_word_item item)
{
	t_word_item	escaped_item;

	word_fpop(&escaped_item, args.word);
	if (!args.is_in_whitelist(escaped_item.c))
	{
		expander->err = word_push(args.word_expanded, item);
		if (expander->err.type)
			return (expander->err);
	}
	return (expander->err = word_push(args.word_expanded, escaped_item));
}

t_error	context_scan(t_expander *expander, t_context_args args)
{
	t_word_item	item;

	while (args.word->len > 0)
	{
		word_fpop(&item, args.word);
		if (!item.opt.is_expand_res && args.is_end != NULL
			&& args.is_end(item.c, NULL))
			return (expander->err);
		if (!item.opt.is_expand_res && item.c == '\\'
			&& args.is_in_whitelist != NULL && args.word->len > 0)
			expander->err = context_escape(expander, args, item);
		else
			expander->err = word_push(args.word_expanded, item);
		if (expander->err.type)
			return (expander->err);
	}
	assert(args.is_end == NULL);
	return (expander->err);
}
