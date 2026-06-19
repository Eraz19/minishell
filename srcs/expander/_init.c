/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 23:14:37 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/19 16:31:02 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "expander_.h"
#include "expander_loader_.h"

void	expander_init(t_expander *state)
{
	*state = (t_expander){0};
	expander_fields_init(&state->fields);
}

void	expander_free(t_expander *state)
{
	expander_fields_free(&state->fields);
	*state = (t_expander){0};
}

t_error	expander_load(t_expander *state, char *word, t_context_stack *stack)
{
	size_t				word_len;
	t_expander_word		word_copy;
	t_expander_loader	loader_state;

	word_len = str_len(word);
	expander_loader_init(&loader_state);
	state->err = expander_loader_load(&loader_state, stack, word);
	if (state->err.type)
		return (expander_loader_free(&loader_state), state->err);
	while (loader_state.i < word_len)
	{
		state->err = expander_loader_build(&loader_state);
		if (state->err.type)
			return (expander_loader_free(&loader_state), state->err);
	}
	state->err = expander_word_dup(&word_copy, &loader_state.loaded_word);
	if (state->err.type)
	{
		expander_loader_free(&loader_state);
		return (expander_word_free(&word_copy), state->err);
	}
	state->err = expander_fields_push(&state->fields, word_copy);
	return (expander_loader_free(&loader_state), state->err);
}
