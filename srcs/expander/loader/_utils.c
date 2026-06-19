/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 13:51:29 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/19 15:44:22 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "expander_loader_.h"

bool	is_char_escaped(t_expander_loader *state)
{
	char	next_char;
	char	current_char;
	bool	is_in_whitelist;

	current_char = state->word[state->i];
	next_char = state->word[state->i + 1];
	if (state->quoting != NONE_)
		is_in_whitelist = is_in_quoting_whitelist(next_char, state->quoting);
	else
		is_in_whitelist = is_in_expansion_whitelist(next_char, state->quoting);
	return (current_char == '\\' && next_char != '\0' && is_in_whitelist);
}

bool	is_substitution_start(t_expander_loader *state)
{
	t_context_stack_item	*item;

	if (state->stack.len == 0)
		return (false);
	state->err = context_stack_get(&state->stack, &item, 0);
	if (state->err || item == NULL)
		return (false);
	return (state->i == item->start);
}

t_error	expander_loader_push_context(t_expander_loader *state)
{
	t_context_stack_item	*item;

	if (state->stack.len == 0)
		return (state->err);
	state->err = context_stack_fpop(&state->stack, &item);
	if (state->err)
		return (state->err);
	state->err = context_stack_push(&state->loading_stack, item);
	if (state->err)
		return (free(item), state->err);
	return (state->context_item = item, state->err);
}

t_error	expander_loader_pop_context(t_expander_loader *state)
{
	t_context_stack_item	*item;
	size_t					last_i;
	
	state->err = context_stack_bpop(&state->loading_stack, &item);
	if (state->err)
		return (state->err);
	free(item);
	if (state->loading_stack.len > 0)
	{
		last_i = state->loading_stack.len - 1;
		state->err = context_stack_get(&state->loading_stack, &item, last_i);
		if (state->err)
			return (state->err);
		state->context_item = item;
	}
	else
		state->context_item = NULL;
	return (state->err);
}

t_error	expander_loader_consume(t_expander_loader *state, size_t count)
{
	size_t					i;
	t_expander_word_item	item;
	t_context				quoting;
	t_context				current;
	char					current_char;
	
	i = 0;
	quoting = state->quoting;
	if (state->context_item == NULL)
		current = NONE_;
	else
		current = state->context_item->context;
	while (i < count)
	{
		current_char = state->word[state->i++];
		item = expander_word_item_init(current_char, quoting, current, false);
		state->err = expander_word_push(&state->loaded_word, item);
		if (state->err)
			return (state->err);
		i++;
	}
	return (state->err);
}
