/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 16:09:23 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/05 20:21:57 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__lexer.h"

t_error	lexer_next_token(t_lexer *state, t_token *token)
{
	t_context	context;

	state->reached_EOI = false;
	state->emited_token = false;
	while (!state->emited_token && !state->reached_EOI)
	{
		if (lexer_rules(state, token, &context))
			return (state->err);
	}
	if (state->reached_EOI)
		lexer_reset(state);
	return (state->err);
}
