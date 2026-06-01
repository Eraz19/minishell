/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 15:31:31 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/29 19:43:09 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_token.h"

bool	lexer_input_end(t_token *res, t_lexer *state) // Rule 1
{
	if (state->input[state->i] == '\0')
	{
		if (state->token.type != NONE)
			return (lexer_delimit_token(res, state), true);
		else
			return (state->reached_EOI = true, true);
	}
	return (false);
}
