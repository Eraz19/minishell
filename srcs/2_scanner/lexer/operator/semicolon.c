/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 10:12:27 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/10 16:52:30 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_operator_.h"

bool	is_operator_char_semicolon(t_lexer *state)
{
	if (state->token.type == SCOLON)
		return (true);
	else if (!is_in_middle_of_operator(state))
		return (true);
	return (false);
}

t_error	operator_add_semicolon(t_lexer *state)
{
	if (state->token.type == SCOLON)
		return (lexer_consume(state, DSEMI, 1));
	else if (state->token.type == NONE)
		return (lexer_consume(state, SCOLON, 1));
	return (state->err = ERR_INCOHERENT_STATE, state->err);
}
