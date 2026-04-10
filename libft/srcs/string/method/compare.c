/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:04:38 by adouieb           #+#    #+#             */
/*   Updated: 2026/02/02 19:50:32 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_string.h"

/**
 * str_cmp - Compares two strings (including NULL strings)
 *
 * @param str1 The first t_cstr to compare
 * @param str2 The second t_cstr to compare
 * @return Negative if str1 < str2, positive if str1 > str2, or 0 if equal
 */
t_i32	str_cmp(t_cstr str1, t_cstr str2)
{
	size_t		i;
	const t_u8	*s1;
	const t_u8	*s2;

	if (str1.s == NULL && str2.s == NULL)
		return (0);
	if (str1.s == NULL)
		return (-1);
	if (str2.s == NULL)
		return (1);
	1 && (i = 0, s1 = (const t_u8 *)str1.s, s2 = (const t_u8 *)str2.s);
	while (i < str1.len && i < str2.len)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		++i;
	}
	if (i < str1.len)
		return (s1[i]);
	if (i < str2.len)
		return (-s2[i]);
	return (0);
}

/**
 * str_start_with - Checks if a string starts with a given prefix
 *
 * @param str The t_cstr to check
 * @param prefix The t_cstr prefix to look for
 * @return TRUE if str starts with prefix, FALSE otherwise
 */
t_bool	str_start_with(t_cstr str, t_cstr prefix)
{
	size_t	i;

	if (str.len < prefix.len)
		return (FALSE);
	i = 0;
	while (i < prefix.len)
	{
		if (str.s[i] != prefix.s[i])
			return (FALSE);
		++i;
	}
	return (TRUE);
}

/**
 * str_end_with - Checks if a string ends with a given suffix
 *
 * @param str The t_cstr to check
 * @param suffix The t_cstr suffix to look for
 * @return TRUE if str ends with suffix, FALSE otherwise
 */
t_bool	str_end_with(t_cstr str, t_cstr suffix)
{
	size_t	i;

	if (str.len < suffix.len)
		return (FALSE);
	i = 0;
	while (i < suffix.len)
	{
		if (str.s[str.len - suffix.len + i] != suffix.s[i])
			return (FALSE);
		++i;
	}
	return (TRUE);
}
