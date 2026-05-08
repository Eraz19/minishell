/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:02:54 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/07 16:36:31 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../_scanner.h"

bool	is_semi_operator(t_token_type *type, char *input_ptr)
{
	if (input_ptr[0] == ';')
	{
		if (input_ptr[1] == ';')
			return (*type = DSEMI, true);
		else if (input_ptr[1] == '&')
			return (*type = SEMI_AND, true);
		return (*type = SCOLON, true);
	}
	return (false);
}

bool	is_ampersand_operator(t_token_type *type, char *input_ptr)
{
	if (input_ptr[0] == '&')
	{
		if (input_ptr[1] == '&')
			return (*type = AND_IF, true);
		return (*type = AMPERSAND, true);
	}
	return (false);
}

bool	is_pipe_operator(t_token_type *type, char *input_ptr)
{
	if (input_ptr[0] == '|')
	{
		if (input_ptr[1] == '|')
			return (*type = OR_IF, true);
		return (*type = PIPE, true);
	}
	return (false);
}

bool	is_newline_operator(t_token_type *type, char *input_ptr)
{
	if (input_ptr[0] == '\n')
		return (*type = NEWLINE, true);
	return (false);
}

bool	is_parenthesis_operator(t_token_type *type, char *input_ptr)
{
	if (input_ptr[0] == '(')
		return (*type = LPARENTHESIS, true);
	else if (input_ptr[0] == ')')
		return (*type = RPARENTHESIS, true);
	return (false);
}
