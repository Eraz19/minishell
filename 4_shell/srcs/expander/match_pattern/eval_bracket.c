/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_bracket.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:44:44 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 17:44:45 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "match_pattern_.h"

bool	eval_range(const char *pattern, char c, size_t *i)
{
	unsigned char	end;
	unsigned char	start;

	start = (unsigned char)pattern[*i];
	end = (unsigned char)pattern[*i + 2];
	if (start <= (unsigned char)c && (unsigned char)c <= end)
		return ((*i) += 3, true);
	else
		return ((*i) += 3, false);
}

bool	eval_bracket_char(const char *pattern, char c, size_t *i)
{
	if (match_char(pattern[*i], c, i))
		return (true);
	else
		return ((*i)++, false);
}

bool	eval_escaped_char(const char *pattern, char c, size_t *i)
{
	(*i)++;
	return (eval_bracket_char(pattern, c, i));
}
