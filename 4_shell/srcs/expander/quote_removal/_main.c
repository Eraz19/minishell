/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:46:05 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 17:46:06 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quote_removal_.h"
#include "quote_removal_context_.h"

static bool	is_opening_mark(t_word_item item)
{
	if (item.opt.escaped)
		return (false);
	if (item.opt.quoted == CONTEXT_SQUOTE)
		return (item.c == '\'');
	if (item.opt.quoted == CONTEXT_DQUOTE)
		return (item.c == '"');
	if (item.opt.quoted == CONTEXT_DOLLAR_SQUOTE)
		return (item.c == '$');
	return (true);
}

static t_error	quote_removal_quoted(t_expander *expander, t_word_item item)
{
	t_word_item	next;

	if (!is_opening_mark(item))
		return (expander->err = word_push(&expander->word_exp, item));
	if (item.opt.quoted == CONTEXT_SQUOTE)
		context_squote(expander);
	else if (item.opt.quoted == CONTEXT_DQUOTE)
		context_dquote(expander);
	else if (item.opt.quoted == CONTEXT_HEREDOC)
		context_heredoc(expander, item);
	else if (item.opt.quoted == CONTEXT_DOLLAR_SQUOTE)
	{
		expander->err = word_get(&next, &expander->word, 0);
		if (expander->err.type)
			return (expander->err);
		if (next.c != '\'')
			return (expander->err = word_push(&expander->word_exp, item));
		expander->err = word_remove(&expander->word, 0, 1);
		if (expander->err.type)
			return (expander->err);
		context_dollar_squote(expander);
	}
	return (expander->err);
}

t_error	quote_remove_char(t_expander *expander)
{
	t_word_item	item;

	expander->err = word_fpop(&item, &expander->word);
	if (expander->err.type)
		return (expander->err);
	if (item.opt.is_expand_res)
		expander->err = word_push(&expander->word_exp, item);
	else if (item.opt.quoted == CONTEXT_NONE)
	{
		if (item.c != '\\')
			expander->err = word_push(&expander->word_exp, item);
		else
		{
			if (expander->word.len == 0)
				return (expander->err = error(ERR_NO));
			expander->err = word_fpop(&item, &expander->word);
			if (expander->err.type)
				return (expander->err);
			expander->err = word_push(&expander->word_exp, item);
		}
	}
	else
		expander->err = quote_removal_quoted(expander, item);
	return (expander->err);
}

static t_error	quote_removal_word(t_expander *expander)
{
	expander->err = fields_fpop(&expander->word, &expander->fields);
	if (expander->err.type)
		return (expander->err);
	word_init(&expander->word_exp);
	while (expander->word.len > 0)
	{
		if (quote_remove_char(expander).type)
			return (expander->err);
	}
	word_free(&expander->word);
	expander->err = fields_push(&expander->fields_exp, expander->word_exp);
	if (expander->err.type)
		return (expander->err);
	return (word_init(&expander->word_exp), expander->err);
}

t_error	quote_removal(t_expander *expander)
{
	fields_init(&expander->fields_exp);
	while (expander->fields.len > 0)
	{
		if (quote_removal_word(expander).type)
			return (fields_free(&expander->fields_exp), expander->err);
	}
	fields_free(&expander->fields);
	expander->fields = expander->fields_exp;
	fields_init(&expander->fields_exp);
	return (expander->err);
}
