/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 10:12:27 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/01 11:20:57 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_operator.h"

bool	is_operator_char_semicolon(t_lexer *state)
{
	if (state->token.type == SCOLON)
		return (true);
	else if (!is_in_middle_of_operator(state))
		return (true);
	return (false);
}

void	operator_add_semicolon(t_lexer *state)
{
	if (state->token.type == SCOLON)
		return (lexer_consume(state, DSEMI, 1));
	else if (state->token.type == NONE)
		return (lexer_consume(state, SCOLON, 1));
}
