/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:21:26 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/09 14:30:45 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../_scanner.h"

t_token	*end_token_by_operator(t_token_type type, int io_number, size_t i)
{
	char *io_number_str;
	
	if (type != IO_NUMBER)
		return (create_token(NULL, i, type));
	else
	{
		io_number_str = ft_itoa(io_number);
		if (io_number_str == NULL)
			return (NULL);
		return (create_token(io_number_str, i, type));
	}
}

bool	is_blank_end_token(char *input_ptr)
{
	return (
		input_ptr[0] == ' ' ||
		input_ptr[0] == '\t' ||
		input_ptr[0] == '\n');
}

t_token	*end_token_by_blank(char *input_ptr, size_t i)
{
	char	*token_value;

	token_value = str_sub(input_ptr, 0, i);
	if (token_value == NULL)
		return (NULL);
	return (create_token(token_value, i, TOKEN));
}
