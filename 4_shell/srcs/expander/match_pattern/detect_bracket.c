/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_bracket.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:44:35 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 17:44:36 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "match_pattern_.h"

bool	valid_char_class_exp_content_len(const char *pattern, size_t *len)
{
	if (str_ncmp(pattern + *len, "alpha", 5) == 0)
		return ((*len) += 5, true);
	else if (str_ncmp(pattern + *len, "digit", 5) == 0)
		return ((*len) += 5, true);
	else if (str_ncmp(pattern + *len, "alnum", 5) == 0)
		return ((*len) += 5, true);
	else if (str_ncmp(pattern + *len, "xdigit", 6) == 0)
		return ((*len) += 6, true);
	else if (str_ncmp(pattern + *len, "lower", 5) == 0)
		return ((*len) += 5, true);
	else if (str_ncmp(pattern + *len, "upper", 5) == 0)
		return ((*len) += 5, true);
	else if (str_ncmp(pattern + *len, "space", 5) == 0)
		return ((*len) += 5, true);
	else if (str_ncmp(pattern + *len, "blank", 5) == 0)
		return ((*len) += 5, true);
	else if (str_ncmp(pattern + *len, "cntrl", 5) == 0)
		return ((*len) += 5, true);
	else if (str_ncmp(pattern + *len, "graph", 5) == 0)
		return ((*len) += 5, true);
	else if (str_ncmp(pattern + *len, "print", 5) == 0)
		return ((*len) += 5, true);
	else if (str_ncmp(pattern + *len, "punct", 5) == 0)
		return ((*len) += 5, true);
	return (false);
}

bool	valid_char_class_exp_len(const char *pattern, size_t *len)
{
	if (valid_char_class_exp_content_len(pattern, len))
	{
		if (pattern[*len] != '\0' && match_char(pattern[*len], ':', len))
		{
			if (pattern[*len] != '\0' && match_char(pattern[*len], ']', len))
				return (true);
		}
	}
	return (false);
}

bool	valid_col_symbol_exp_len(const char *pattern, size_t *len)
{
	if (pattern[*len] == '\0')
		return (false);
	(*len)++;
	if (pattern[*len] != '\0' && match_char(pattern[*len], '.', len))
	{
		if (pattern[*len] != '\0' && match_char(pattern[*len], ']', len))
			return (true);
	}
	return (false);
}

bool	valid_equ_class_exp_len(const char *pattern, size_t *len)
{
	if (pattern[*len] == '\0')
		return (false);
	(*len)++;
	if (pattern[*len] != '\0' && match_char(pattern[*len], '=', len))
	{
		if (pattern[*len] != '\0' && match_char(pattern[*len], ']', len))
			return (true);
	}
	return (false);
}

bool	valid_sub_exp_len(const char *pattern, size_t *len)
{
	size_t	len_copy;

	len_copy = *len;
	if (match_char(pattern[*len], ':', len))
	{
		if (valid_char_class_exp_len(pattern, len))
			return (true);
	}
	else if (match_char(pattern[*len], '.', len))
	{
		if (valid_col_symbol_exp_len(pattern, len))
			return (true);
	}
	else if (match_char(pattern[*len], '=', len))
	{
		if (valid_equ_class_exp_len(pattern, len))
			return (true);
	}
	return (*len = len_copy, false);
}
