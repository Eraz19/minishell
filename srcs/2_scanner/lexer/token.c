/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 11:50:16 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/01 09:35:45 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./_lexer.h"
#include "./token/_token.h"

void	lexer_token_recognition(t_token *res, t_lexer *state)
{
	while (!state->emited_token && !state->reached_EOI)
	{
		if (state->err)
			return ;
		if (lexer_input_end(res, state))
			continue ;
		else if (lexer_in_middle_of_operator(res, state))
			continue ;
		else if (lexer_quoting(state))
			continue ;
		else if (lexer_substitution(state))
			continue ;
		else if (lexer_new_operator(res, state))
			continue ;
		else if (lexer_blank(res, state))
			continue ;
		else if (lexer_in_middle_of_word(state))
			continue ;
		else if (lexer_comment(state))
			continue ;
		else
			lexer_new_word(state);
	}
	if (state->reached_EOI)
		lexer_reset(state);
}
