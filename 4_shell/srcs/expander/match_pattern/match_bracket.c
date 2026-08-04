/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_bracket.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 18:15:03 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 18:16:12 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "match_patern_.h"

bool	match_bracket(const char *pattern, const char *str, size_t len)
{
	size_t	exp_len;

	if (len == 0)
		return (false);
	exp_len = 0;
	if (valid_bracket_exp_len(pattern + 1, &exp_len))
	{
		if (match_bracket_c(pattern, exp_len, *str))
			return (match_pattern(pattern + exp_len + 2, str + 1, len - 1));
	}
	else if (*str == '[')
		return (match_pattern(pattern + 1, str + 1, len - 1));
	return (false);
}
