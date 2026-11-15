/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:46:15 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/06 00:23:30 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_.h"
#include "arith_substitution_.h"

bool	is_arith_substitution(t_word_item *current_item, uint flags)
{
	if (!flag_is_active(flags, EXP_ARITH))
		return (false);
	if (current_item->opt.context == CONTEXT_ARITH)
		return (true);
	return (false);
}

t_error	extract_arith_word(t_expander *expander, t_word *word)
{
	size_t		i;
	size_t		len;
	t_word_item	item;

	word_get(&item, &expander->word, 0);
	i = 0;
	len = item.opt.context_len;
	word_init(word);
	while (i < len)
	{
		word_fpop(&item, &expander->word);
		if (i > 2 && i < len - 2)
		{
			item.opt.quoted = CONTEXT_DQUOTE;
			expander->err = word_push(word, item);
			if (expander->err.type)
				return (word_free(word), expander->err);
		}
		++i;
	}
	return (expander->err);
}

t_error	build_arith_expander(
			t_expander *arith_expander,
			t_expander *expander,
			t_word *arith_word)
{
	expander_init(arith_expander);
	expander->err = fields_push(&arith_expander->fields, *arith_word);
	if (expander->err.type)
	{
		word_free(arith_word);
		return (expander_free(arith_expander), expander->err);
	}
	arith_expander->ifs = expander->ifs;
	arith_expander->flags = EXP_PARAM | EXP_CMD_SUB | EXP_QUOTE_REMOVAL;
	return (expander->err);
}

t_error	compute_arith_expression(t_expander *expander, t_expansion *expansion)
{
	(void)expansion;
	expander->err = error_print(
			error(ERR_NOT_IMPLEMENTED),
			"expander",
			"arithmetic expansion not implemented",
			NULL, NULL);
	expander->err.type = ERR_INTERNAL;
	return (expander->err);
}

t_error	arith_substitution(t_expander *expander)
{
	t_expansion	expansion;
	t_word		arith_word;
	t_expander	arith_expander;

	if (extract_arith_word(expander, &arith_word).type)
		return (expander->err);
	if (build_arith_expander(&arith_expander, expander, &arith_word).type)
		return (expander->err);
	expander->err = expand_word(&arith_expander);
	if (expander->err.type)
		return (expander_free(&arith_expander), expander->err);
	expansion_init(&expansion);
	expander->err = expansion_load(&expansion, &arith_expander.fields);
	if (!expander->err.type)
		expander->err = compute_arith_expression(expander, &expansion);
	expander_free(&arith_expander);
	return (expansion_free(&expansion), expander->err);
}
