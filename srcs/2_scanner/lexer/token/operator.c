/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 15:33:31 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/01 09:53:18 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_token.h"
#include "../operator/_operator.h"

bool	lexer_in_middle_of_operator(t_token *res, t_lexer *state) // Rule 2-3
{
	if (is_in_middle_of_operator(state))
	{
		if (lexer_is_operator_char(state)) // Rule 2
			return (lexer_char_into_token_operator(state), true);
		else
			return (lexer_delimit_token(res, state), true); // Rule 3
	}
	return (false);
}

bool	lexer_new_operator(t_token *res, t_lexer *state) // Rule 6
{
	if (!is_in_middle_of_operator(state) && lexer_is_operator_char(state))
	{
		if (state->token.type != NONE)
			return (lexer_delimit_token(res, state), true);
		else
			return (lexer_char_into_token_operator(state), true);
	}
	return (false);
}
