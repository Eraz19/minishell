/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 13:37:43 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/19 15:40:08 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "expander_loader_.h"

void	expander_loader_init(t_expander_loader *state)
{
	*state = (t_expander_loader){0};
	context_stack_init(&state->stack);
	expander_word_init(&state->loaded_word);
	context_stack_init(&state->loading_stack);
}

void	expander_loader_free(t_expander_loader *state)
{
	context_stack_free(&state->stack);
	expander_word_free(&state->loaded_word);
	context_stack_free(&state->loading_stack);
	if (state->context_item)
		state->context_item = NULL;
	*state = (t_expander_loader){0};
}

t_error	expander_loader_load(
	t_expander_loader *state,
	t_context_stack *stack,
	char *word)
{
	state->word = word;
	if (stack == NULL)
		return (state->err);
	return (state->err = context_stack_dup(&state->stack, stack));
}
