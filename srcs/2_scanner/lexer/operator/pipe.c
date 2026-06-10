/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 10:11:31 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/10 16:52:25 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_operator_.h"

bool	is_operator_char_pipe(t_lexer *state)
{
	if (state->token.type == PIPE)
		return (true);
	else if (state->token.type == GREAT)
		return (true);
	else if (!is_in_middle_of_operator(state))
		return (true);
	return (false);
}

t_error	operator_add_pipe(t_lexer *state)
{
	if (state->token.type == PIPE)
		return (lexer_consume(state, OR_IF, 1));
	else if (state->token.type == GREAT)
		return (lexer_consume(state, CLOBBER, 1));
	else if (state->token.type == NONE)
		return (lexer_consume(state, PIPE, 1));
	return (state->err = ERR_INCOHERENT_STATE, state->err);
}
