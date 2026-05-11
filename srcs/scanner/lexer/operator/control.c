/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:02:54 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/10 14:42:05 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../_scanner.h"

bool	is_semi(t_lexer *lexer, t_operator_args *args, size_t i)
{
	char	*input_ptr;

	input_ptr = lexer->input + i;
	if (input_ptr[0] == ';')
	{
		if (input_ptr[1] == ';')
			return (args->type = DSEMI, args->len = 2, true);
		else if (input_ptr[1] == '&')
			return (args->type = SEMI_AND, args->len = 2, true);
		return (args->type = SCOLON, args->len = 1, true);
	}
	return (false);
}

bool	is_ampersand(t_lexer *lexer, t_operator_args *args, size_t i)
{
	char	*input_ptr;

	input_ptr = lexer->input + i;
	if (input_ptr[0] == '&')
	{
		if (input_ptr[1] == '&')
			return (args->type = AND_IF, args->len = 2, true);
		return (args->type = AMPERSAND, args->len = 1, true);
	}
	return (false);
}

bool	is_pipe(t_lexer *lexer, t_operator_args *args, size_t i)
{
	char	*input_ptr;

	input_ptr = lexer->input + i;
	if (input_ptr[0] == '|')
	{
		if (input_ptr[1] == '|')
			return (args->type = OR_IF, args->len = 2, true);
		return (args->type = PIPE, args->len = 1, true);
	}
	return (false);
}

bool	is_newline(t_lexer *lexer, t_operator_args *args, size_t i)
{
	char	*input_ptr;

	input_ptr = lexer->input + i;
	if (input_ptr[0] == '\n')
		return (args->type = NEWLINE, args->len = 1, true);
	return (false);
}

bool	is_parenthesis(t_lexer *lexer, t_operator_args *args, size_t i)
{
	char	*input_ptr;

	input_ptr = lexer->input + i;
	if (input_ptr[0] == '(')
		return (args->type = LPARENTHESIS, args->len = 1, true);
	else if (input_ptr[0] == ')')
		return (args->type = RPARENTHESIS, args->len = 1, true);
	return (false);
}
