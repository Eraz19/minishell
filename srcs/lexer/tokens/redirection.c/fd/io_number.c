/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_number.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 12:08:02 by adouieb           #+#    #+#             */
/*   Updated: 2026/04/27 14:51:35 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../../_lexer.h"

t_lexer_token	*io_number(size_t offset)
{
	t_lexer_token	*res;

	res = malloc(sizeof(t_lexer_token));
	if (res == NULL)
		return (NULL);
	res->offset = offset;
	res->type = REDIRECTION_;
	res->id.redirection_ = IO_NUMBER;
	if (buff_init(&res->value, 0) == false)
		return (free(res), NULL);
	return (res);
}

static bool	is_io_number_in_bounds(t_raw_string input_ptr, size_t offset)
{
	int				value;
	t_raw_string	number_str;

	number_str = str_sub(input_ptr, 0, offset);
	if (number_str == NULL)
		return (false);
	if (parse_int(number_str, &value) == false)
		return (free(number_str), false);
	return (free(number_str), true);
}

static bool	is_number_followed_by_redirection(t_raw_string input_ptr, size_t i)
{
	if (is_less(input_ptr + i))
		return (true);
	else if (is_great(input_ptr + i))
		return (true);
	else if (is_dless(input_ptr + i))
		return (true);
	else if (is_dgreat(input_ptr + i))
		return (true);
	else if (is_lessand(input_ptr + i))
		return (true);
	else if (is_greatand(input_ptr + i))
		return (true);
	else if (is_lessgreat(input_ptr + i))
		return (true);
	else if (is_clobber(input_ptr + i))
		return (true);
	else if (is_dlessdash(input_ptr + i))
		return (true);
	return (false);
}

bool	is_io_number(t_raw_string input_ptr)
{
	size_t	i;

	i = 0;
	while (input_ptr[i] && input_ptr[i] >= '0' && input_ptr[i] <= '9')
		i++;
	if (i == 0)
		return (false);
	else if (is_io_number_in_bounds(input_ptr, i) == false)
		return (false);
	else if (is_number_followed_by_redirection(input_ptr, i) == false)
		return (false);
	return (true);
}
