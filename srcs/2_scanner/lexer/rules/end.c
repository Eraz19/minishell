/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 15:31:31 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/05 20:20:37 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__lexer_rules.h"

bool	is_end(t_lexer *state)
{
	return (state->input[state->i] == '\0');
}

t_error	lexer_rule_end(t_lexer *state, t_token *token)
{
	if (state->token.type != NONE)
		return (lexer_delimit_token(state, token));
	else
		return (state->reached_EOI = true, state->err);
}
