/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   great.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 10:09:51 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/05 20:18:07 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__lexer_operator.h"

bool	is_operator_char_great(t_lexer *state)
{
	if (state->token.type == LESS)
		return (true);
	else if (state->token.type == GREAT)
		return (true);
	else if (!is_in_middle_of_operator(state))
		return (true);
	return (false);
}

t_error	operator_add_great(t_lexer *state)
{
	if (state->token.type == LESS)
		return (lexer_consume(state, LESSGREAT, 1));
	else if (state->token.type == GREAT)
		return (lexer_consume(state, DGREAT, 1));
	else if (state->token.type == NONE)
		return (lexer_consume(state, GREAT, 1));
	return (state->err = ERR_INCOHERENT_STATE, state->err);
}
