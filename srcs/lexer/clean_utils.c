/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 15:22:43 by adouieb           #+#    #+#             */
/*   Updated: 2026/04/27 15:22:53 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_lexer.h"

t_raw_string	remove_escapable_newlines(t_raw_string input)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '\\' && input[i + 1] == '\n')
		{
			i += 2;
			continue ;
		}
		input[j++] = input[i++];
	}
	input[j] = '\0';
	return (input);
}
