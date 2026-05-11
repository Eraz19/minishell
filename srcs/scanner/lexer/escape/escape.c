/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:19:05 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/07 16:19:46 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	escape_char_in_param(char *input_ptr, size_t *i)
{
	if (input_ptr[1] == '\n')
	{
		ft_memmove(input_ptr, input_ptr + 2, str_len(input_ptr + 2));
		return (true);
	}
	else
		return ((*i) += 2, true);
}

bool	escape_char_in_arithm(char *input_ptr, size_t *i)
{
	if (input_ptr[1] == '\n')
	{
		ft_memmove(input_ptr, input_ptr + 2, str_len(input_ptr + 2));
		return (true);
	}
	else
		return ((*i) += 2, true);
}

bool	escape_char_in_backtick(size_t *i)
{
	return ((*i) += 2, true);
}

bool	escape_char_in_dquote(char *input_ptr, size_t *i)
{
	if (input_ptr[1] == '\n')
	{
		ft_memmove(input_ptr, input_ptr + 2, str_len(input_ptr + 2));
		return (true);
	}
	else
		return ((*i) += 2, true);
}

bool	escape_char_in_no_ctx(char *input_ptr, size_t *i)
{
	if (input_ptr[1] == '\n')
	{
		ft_memmove(input_ptr, input_ptr + 2, str_len(input_ptr + 2));
		return (true);
	}
	return ((*i) += 2, true);
}
