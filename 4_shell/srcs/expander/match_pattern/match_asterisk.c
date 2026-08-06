/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_asterisk.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 18:17:18 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/05 15:48:52 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expander_.h"
#include "match_pattern_.h"

bool	match_asterisk(const char *pattern, const char *str, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	pattern_len;

	i = 0;
	pattern_len = str_len(pattern);
	while (i < pattern_len && pattern[i] == '*')
		i++;
	if (i == pattern_len)
		return (true);
	j = 0;
	while (j < len)
	{
		if (match_pattern(pattern + i, str + j, len - j))
			return (true);
		j++;
	}
	return (false);
}
