/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 15:33:31 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/10 16:53:24 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_rules_.h"
#include "lexer_operator_.h"

bool	is_new_operator(t_lexer *state)
{
	return (!is_in_middle_of_operator(state) && is_operator_char(state));
}

t_error	lexer_rule_in_middle_of_operator(t_lexer *state, t_token *token) // Rule 2-3
{
	if (is_operator_char(state)) // Rule 2
		return (lexer_add_char_into_token_operator(state), state->err);
	else
		return (lexer_delimit_token(state, token)); // Rule 3
}

t_error	lexer_rule_new_operator(t_lexer *state, t_token *token) // Rule 6
{
	if (state->token.type != NONE)
		return (lexer_delimit_token(state, token));
	else
		return (lexer_add_char_into_token_operator(state), state->err);
}
