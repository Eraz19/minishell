/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 10:11:31 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/01 11:20:28 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_operator.h"

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

void	operator_add_pipe(t_lexer *state)
{
	if (state->token.type == PIPE)
		return (lexer_consume(state, OR_IF, 1));
	else if (state->token.type == GREAT)
		return (lexer_consume(state, CLOBBER, 1));
	else if (state->token.type == NONE)
		return (lexer_consume(state, PIPE, 1));
}
