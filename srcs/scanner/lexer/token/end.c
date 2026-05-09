/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:21:26 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/09 17:03:02 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../_scanner.h"

t_token	*end_token_by_operator(t_token_type type, int io_number, size_t start)
{
	char *io_number_str;
	
	if (type != IO_NUMBER)
		return (create_token(NULL, start, type));
	else
	{
		io_number_str = ft_itoa(io_number);
		if (io_number_str == NULL)
			return (NULL);
		return (create_token(io_number_str, start, type));
	}
}

bool	is_blank_end_token(char *input_ptr)
{
	return (input_ptr[0] == ' ' || input_ptr[0] == '\t');
}

t_token	*end_token_by_blank(char *input, size_t start, size_t i)
{
	char	*token_value;

	ft_printf("INPUT_PTR = '%s' | START = %d | INDEX = %d\n", input, (int)start, (int)i);
	token_value = str_sub(input, (uint)start, i - start);
	if (token_value == NULL)
		return (NULL);
	return (create_token(token_value, start, TOKEN));
}
