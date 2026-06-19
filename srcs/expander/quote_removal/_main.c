/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:21:57 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/19 10:20:43 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "quote_removal_.h"
#include "quote_removal_context_.h"

t_error	quote_removal_quoted(
	t_expander *state,
	t_context context,
	t_expander_word *word,
	t_expander_word *word_expanded)
{
	t_expander_word_item	item;

	if (context == SQUOTE)
		context_squote(state, word, word_expanded);
	else if (context == DQUOTE)
		context_dquote(state, word, word_expanded);
	else if (context == DOLLAR_SQUOTE)
	{
		state->err = expander_word_pop(word, &item);
		if (state->err)
			return (state->err);
		context_dollar_squote(state, word, word_expanded);
	}
	return (state->err);
}

t_error	quote_remove_char(
	t_expander *state,
	t_expander_word *word,
	t_expander_word *word_exp)
{
	t_expander_word_item	item;

	state->err = expander_word_pop(word, &item);
	if (state->err)
		return (state->err);
	if (item.is_expand_res)
		state->err = expander_word_push(word_exp, item);
	else if (item.quoted == NONE_)
	{
		if (item.c != '\\')
			state->err = expander_word_push(word_exp, item);
		else
		{
			if (word->len == 0)
				return (state->err = ERR_NO);
			state->err = expander_word_pop(word, &item);
			if (state->err)
				return (state->err);
			state->err = expander_word_push(word_exp, item);
		}
	}
	else
		quote_removal_quoted(state, item.quoted, word, word_exp);
	return (state->err);
}

t_error	quote_removal_word(t_expander *state, t_expander_fields *fields)
{
	t_expander_word	word;
	t_expander_word	word_exp;

	state->err = expander_fields_pop(&state->fields, &word);
	if (state->err)
		return (state->err);
	expander_word_init(&word_exp);
	while (word.len > 0)
	{
		if (quote_remove_char(state, &word, &word_exp))
		{
			expander_word_free(&word);
			expander_word_free(&word_exp);
			return (state->err);
		}
	}
	expander_word_free(&word);
	state->err = expander_fields_push(fields, word_exp);
	if (state->err)
		expander_word_free(&word_exp);
	return (state->err);
}

t_error	quote_removal(t_expander *state)
{
	t_expander_fields	fields;

	expander_fields_init(&fields);
	while (state->fields.len > 0)
	{
		if (quote_removal_word(state, &fields))
			return (expander_fields_free(&fields), state->err);
	}
	expander_fields_free(&state->fields);
	state->fields = fields;
	return (state->err);
}
