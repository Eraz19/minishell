/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 15:37:26 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/01 09:53:18 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_token.h"

bool	lexer_quoting(t_lexer *state) // Rule 4
{
	const char	*input_ptr;

	input_ptr = state->input + state->i;
	if (input_ptr[0] == '\'')
		return (lexer_context(state, SQUOTE));
	else if (input_ptr[0] == '$' && input_ptr[1] == '\'')
		return (lexer_context(state, DOLLAR_SQUOTE));
	else if (input_ptr[0] == '\"')
		return (lexer_context(state, DQUOTE));
	return (false);
}

bool	lexer_substitution(t_lexer *state)  // Rule 5
{
	if (state->input[state->i] == '$')
	{
		if (state->input[state->i + 1] == '{')
			return (lexer_context(state, PARAM));
		else if (state->input[state->i + 1] == '(')
		{
			if (state->input[state->i + 2] == '(')
			{
				if (lexer_context(state, ARITH) || state->err)
					return (true);
			}
			return (lexer_context(state, CMD_SUB));
		}
	}
	else if (state->input[state->i] == '`')
		return (lexer_context(state, BACKTICK));
	return (false);
}
