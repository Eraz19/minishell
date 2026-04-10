/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:17:47 by adouieb           #+#    #+#             */
/*   Updated: 2026/02/02 19:51:02 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_string.h"

/**
 * str_trim_char - Trims characters from the beginning and end of a string
 *
 * MEMORY OWNERSHIP: This function consumes (frees) the input 'str', the
 * original 'str' becomes invalid.
 * To keep a copy of the string, first duplicate it before.
 * Always reassign the result:
 *     t_dstr str_copy = dstr_d(original_str);
 *     str_copy = str_trim_char(&str_copy, set); // ✓ Correct usage
 *     original_str                              // ✓ remains valid
 *
 * @param str The t_dstr to trim (always freed)
 * @param set The t_cstr containing characters to remove
 * @return A new t_dstr with trimmed content
 *
 * @args: If str.s is NULL, returns a NULL t_dstr.
 *        If set.s is NULL, returns a duplicate of str.
 * @error: If allocation fails, returns a NULL t_dstr (errno ENOMEM).
 * INFO: If all characters are trimmed, returns an empty string (not NULL).
 */
t_dstr	str_trim_char(t_dstr *str, t_cstr set)
{
	t_dstr	res;
	size_t	end;
	size_t	start;

	if (str->s == NULL)
		return (free_dstr(str), dstr_s(0));
	if (set.s == NULL)
		return (res = dstr_d(*str), free_dstr(str), res);
	1 && (start = 0, end = str->len);
	while (start < str->len && str_findchr(set, str->s[start]).s)
		++start;
	while (end > start && str_findchr(set, str->s[end - 1]).s)
		--end;
	if (start == end)
		return (free_dstr(str), dstr_s(1));
	res = str_sub(cstr_d(*str), start, end - start);
	free_dstr(str);
	return (res);
}

/**
 * str_trim_str - Trims substrings from the beginning and end of a string
 *
 * MEMORY OWNERSHIP: This function consumes (frees) the input 'str1', the
 * original 'str1' becomes invalid.
 * To keep a copy of the string, first duplicate it before.
 * Always reassign the result:
 *     t_dstr str_copy = dstr_d(original_str);
 *     str_copy = str_trim_str(&str_copy, set); // ✓ Correct usage
 *     original_str                             // ✓ remains valid
 *
 * @param str1 The t_dstr to trim (always freed)
 * @param str2 The t_cstr containing substrings to remove
 * @return A new t_dstr with trimmed content
 *
 * @args: If str1.s is NULL, returns a NULL t_dstr.
 *        If str2.s is NULL, returns a duplicate of str1.
 * @error: If allocation fails, returns a NULL t_dstr (errno ENOMEM).
 * INFO: If all characters are trimmed, returns an empty string (not NULL).
 */
t_dstr	str_trim_str(t_dstr *str1, t_cstr str2)
{
	t_dstr	res;
	size_t	end;
	t_cstr	str1_;
	size_t	start;

	if (str1->s == NULL)
		return (free_dstr(str1), dstr_s(0));
	if (str2.s == NULL)
		return (res = dstr_d(*str1), free_dstr(str1), res);
	1 && (start = 0, end = str1->len);
	str1_ = cstr_d(*str1);
	while (start < str1->len && str_start_with(str1_, str2) == TRUE)
		1 && (str1_ = str_cshift(str1_, str2.len), start += str2.len);
	str1_ = cstr_d(*str1);
	while (end > start && str_end_with(str1_, str2) == TRUE)
		1 && (str1_ = str_cshrink(str1_, str2.len), end -= str2.len);
	if (start == end)
		return (free_dstr(str1), dstr_s(1));
	res = str_sub(cstr_d(*str1), start, end - start);
	free_dstr(str1);
	return (res);
}
