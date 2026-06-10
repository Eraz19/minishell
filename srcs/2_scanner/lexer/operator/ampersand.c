/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ampersand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 10:12:04 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/10 16:52:10 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_operator_.h"

bool	is_operator_char_ampersand(t_lexer *state)
{
	if (state->token.type == SCOLON)
		return (true);
	else if (state->token.type == AMPERSAND)
		return (true);
	else if (state->token.type == LESS)
		return (true);
	else if (state->token.type == GREAT)
		return (true);
	else if (!is_in_middle_of_operator(state))
		return (true);
	return (false);
}

t_error	operator_add_ampersand(t_lexer *state)
{
	if (state->token.type == SCOLON)
		return (lexer_consume(state, SEMI_AND, 1));
	else if (state->token.type == AMPERSAND)
		return (lexer_consume(state, AND_IF, 1));
	else if (state->token.type == LESS)
		return (lexer_consume(state, LESSAND, 1));
	else if (state->token.type == GREAT)
		return (lexer_consume(state, GREATAND, 1));
	else if (state->token.type == NONE)
		return (lexer_consume(state, AMPERSAND, 1));
	return (state->err = ERR_INCOHERENT_STATE, state->err);
}
