/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 15:31:31 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/10 16:53:20 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_rules_.h"

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
