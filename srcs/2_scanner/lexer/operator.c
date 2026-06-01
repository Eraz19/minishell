/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 10:08:14 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/01 11:21:12 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./_lexer.h"
#include "./operator/_operator.h"

bool	lexer_is_operator_char(t_lexer *state)
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

void	lexer_char_into_token_operator(t_lexer *state)
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
}
