/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 16:09:23 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/10 18:54:33 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_.h"

t_error	lexer_next_token(t_lexer *state, t_token *token)
{
	t_context	context;

	state->reached_EOI = false;
	state->emited_token = false;
	state->err = input_stack_get_last(&state->input_stack, &state->input);
	if (state->err)
		return (state->err);
	while (!state->emited_token && !state->reached_EOI)
	{
		if (lexer_rules(state, token, &context))
			return (state->err);
	}
	if (state->reached_EOI)
		state->err = input_stack_pop(&state->input_stack);
	return (state->input = (t_input_stack_item){0}, state->err);
}
