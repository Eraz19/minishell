/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blank.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 15:38:40 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/01 11:22:40 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_token.h"

static bool	is_blank(t_lexer *state)
{
	return (state->input[state->i] == ' ' || state->input[state->i] == '\t');
}

bool	lexer_blank(t_token *res, t_lexer *state) // Rule 7
{
	if (is_blank(state))
	{
		if (state->token.type != NONE)
			return (lexer_delimit_token(res, state), true);
		while (is_blank(state) && state->input[state->i] != '\0')
			state->i++;
		return (true);
	}
	return (false);
}
