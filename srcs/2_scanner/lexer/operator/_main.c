/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 19:23:30 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/10 16:52:00 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_operator_.h"

bool	is_operator_char(t_lexer *state)
{
	const char	*input_ptr;

	input_ptr = state->input + state->i;
	if (input_ptr[0] == '\n' && !is_in_middle_of_operator(state))
		return (true);
	else if (input_ptr[0] == '(' && !is_in_middle_of_operator(state))
		return (true);
	else if (input_ptr[0] == ')' && !is_in_middle_of_operator(state))
		return (true);
	else if (input_ptr[0] == ';')
		return (is_operator_char_semicolon(state));
	else if (input_ptr[0] == '&')
		return (is_operator_char_ampersand(state));
	else if (input_ptr[0] == '|')
		return (is_operator_char_pipe(state));
	else if (input_ptr[0] == '<')
		return (is_operator_char_less(state));
	else if (input_ptr[0] == '>')
		return (is_operator_char_great(state));
	else if (input_ptr[0] == '-' && state->token.type == DLESS)
		return (true);
	return (false);
}

t_error	lexer_add_char_into_token_operator(t_lexer *state)
{
	const char	*input_ptr;

	input_ptr = state->input + state->i;
	if (input_ptr[0] == '\n')
		return (lexer_consume(state, NEWLINE_, 1));
	else if (input_ptr[0] == '(')
		return (lexer_consume(state, LPARENTHESIS, 1));
	else if (input_ptr[0] == ')')
		return (lexer_consume(state, RPARENTHESIS, 1));
	else if (input_ptr[0] == ';')
		return (operator_add_semicolon(state));
	else if (input_ptr[0] == '&')
		return (operator_add_ampersand(state));
	else if (input_ptr[0] == '|')
		return (operator_add_pipe(state));
	else if (input_ptr[0] == '<')
		return (operator_add_less(state));
	else if (input_ptr[0] == '>')
		return (operator_add_great(state));
	else if (input_ptr[0] == '-')
		return (lexer_consume(state, DLESSDASH, 1));
	return (state->err = ERR_INCOHERENT_STATE, state->err);
}
