/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:01:42 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/07 16:36:55 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../_scanner.h"

bool	is_less_operator(t_token_type *type, char *input_ptr)
{
	if (input_ptr[0] == '<')
	{
		if (input_ptr[1] == '>')
			return (*type = LESSGREAT, true);
		else if (input_ptr[1] == '&')
			return (*type = LESSAND, true);
		else if (input_ptr[1] == '<')
		{
			if (input_ptr[2] == '-')
				return (*type = DLESSDASH, true);
			return (*type = DLESS, true);
		}
		return (*type = LESS, true);
	}
	return (false);
}

bool	is_great_operator(t_token_type *type, char *input_ptr)
{
	if (input_ptr[0] == '>')
	{
		if (input_ptr[1] == '&')
			return (*type = GREATAND, true);
		else if (input_ptr[1] == '|')
			return (*type = CLOBBER, true);
		else if (input_ptr[1] == '>')
			return (*type = DGREAT, true);
		return (*type = GREAT, true);
	}
	return (false);
}

bool	is_io_number_operator(t_token_type *type, int *value, char * input_ptr)
{
	size_t			i;
	int				number;
	char			*number_str;
	t_token_type	redirection_type;

	i = 0;
	while (input_ptr[i] && input_ptr[i] >= '0' && input_ptr[i] <= '9')
		i++;
	if (i == 0)
		return (false);
	number_str = str_sub(input_ptr, 0, i);
	if (number_str == NULL)
		return (false);
	if (parse_int(number_str, &number) == false)
		return (free(number_str), false);
	free(number_str);		
	if (!is_less_operator(&redirection_type, input_ptr + i) &&
		!is_great_operator(&redirection_type, input_ptr + i))
		return (false);
	return (*type = IO_NUMBER, *value = number, true);
}
