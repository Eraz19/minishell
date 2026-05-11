/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:01:42 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/10 15:12:06 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../_scanner.h"

bool	is_less(t_lexer *lexer, t_operator_args *args, size_t i)
{
	char	*input_ptr;

	input_ptr = lexer->input + i;
	if (input_ptr[0] == '<')
	{
		if (input_ptr[1] == '>')
			return (args->type = LESSGREAT, args->len = 2, true);
		else if (input_ptr[1] == '&')
			return (args->type = LESSAND, args->len = 2, true);
		else if (input_ptr[1] == '<')
		{
			if (input_ptr[2] == '-')
				return (args->type = DLESSDASH, args->len = 3, true);
			return (args->type = DLESS, args->len = 2, true);
		}
		return (args->type = LESS, args->len = 1, true);
	}
	return (false);
}

bool	is_great(t_lexer *lexer, t_operator_args *args, size_t i)
{
	char	*input_ptr;

	input_ptr = lexer->input + i;
	if (input_ptr[0] == '>')
	{
		if (input_ptr[1] == '&')
			return (args->type = GREATAND, args->len = 2, true);
		else if (input_ptr[1] == '|')
			return (args->type = CLOBBER, args->len = 2, true);
		else if (input_ptr[1] == '>')
			return (args->type = DGREAT, args->len = 2, true);
		return (args->type = GREAT, args->len = 1, true);
	}
	return (false);
}

bool	is_io_number(t_lexer *lexer, t_operator_args *args, size_t i)
{
	size_t	j;
	int		number;
	char	*input_ptr;
	char	*number_str;

	j = 0;
	input_ptr = lexer->input + i;
	if (lexer->i != i)
		return (false);
	while (input_ptr[j] && input_ptr[j] >= '0' && input_ptr[j] <= '9')
		j++;
	if (j == 0)
		return (false);
	number_str = str_sub(input_ptr, 0, j);
	if (number_str == NULL)
		return (false);
	if (parse_int(number_str, &number) == false)
		return (free(number_str), false);
	free(number_str);
	if (is_less(lexer, args, i + j))
		return (args->type = IO_NUMBER, args->value = number, args->len = (int)j, true);	
	else if (is_great(lexer, args, i + j))
		return (args->type = IO_NUMBER, args->value = number, args->len = (int)j, true);
	return (false);
}
