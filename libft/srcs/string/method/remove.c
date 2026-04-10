/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 20:48:24 by adouieb           #+#    #+#             */
/*   Updated: 2026/02/05 22:18:03 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_string.h"

/**
 * get_next_sub_string - Extract the next substring before the match
 *
 * @param str The remaining string to process
 * @param next_match The next occurrence of the remove_str in str
 * @return A t_dstr of the substring before the match
 *
 * @error: If allocation fails, returns a NULL t_dstr.
 * @infos: If no match is found, return a copy of the all string
 */
static t_dstr	get_next_sub_string(
	t_cstr str,
	t_cstr next_match)
{
	if (next_match.s == NULL)
		return (str_sub(str, 0, str.len));
	else
		return (str_sub(str, 0, (size_t)(next_match.s - str.s)));
}

/**
 * str_shift_ - Shift the string to remove the processed part
 *
 * @param str The remaining string to process
 * @param next_match The next occurrence of the remove_str in str
 * @param removed_str_len The length of the substring being removed
 * @return A t_cstr of the remaining string after shifting
 */
static t_cstr	str_shift_(
	t_cstr str,
	t_cstr next_match,
	t_cstr removed_str_len)
{
	size_t	shift_len;

	if (next_match.s == NULL)
		shift_len = str.len;
	else
		shift_len = (size_t)(next_match.s - str.s) + removed_str_len.len;
	return (str_cshift(str, shift_len));
}

/**
 * str_cremove - Remove all occurrences of a substring from a string
 *
 * @param str The t_cstr structure to remove from
 * @param remove_str The t_cstr structure to remove
 * @return A new t_dstr with the specified substring removed
 *
 * @error: If allocation fails, returns a NULL t_dstr.
 * @args: If str.s is NULL, returns a NULL t_dstr.
 * 		  If remove_str.s is NULL or empty, returns a copy of str.
 */
t_dstr	str_cremove(
	t_cstr str,
	t_cstr remove_str)
{
	t_dstr	res;
	t_cstr	match;
	t_dstr	sub_str;

	if (str.s == NULL)
		return (dstr_s(0));
	if (remove_str.s == NULL || remove_str.len == 0)
		return (dstr_c(str));
	res = dstr_s(1);
	while (str.len > 0)
	{
		match = str_findsub(str, remove_str);
		sub_str = get_next_sub_string(str, match);
		if (sub_str.s == NULL)
			return (free_dstr(&res), dstr_s(0));
		res = str_insert(&res, &sub_str, res.len);
		if (res.s == NULL)
			return (free_dstr(&res), free_dstr(&sub_str), dstr_s(0));
		str = str_shift_(str, match, remove_str);
	}
	return (res);
}

/**
 * str_dremove - Remove all occurrences of a substring from a dynamic string
 *
 * MEMORY OWNERSHIP: This function consumes (frees) the input 'str', the
 * original 'str' becomes invalid.
 * To keep a copy of the string, first duplicate it before:
 *     t_dstr str_copy = dstr_d(original_str);
 *     t_dstr str = str_dremove(&str_copy, remove_str);
 *     original_str // ✓ remains valid.
 *
 * @param str A pointer to the t_dstr structure to remove from (always freed)
 * @param remove_str The t_cstr structure to remove
 * @return A new t_dstr with the specified substring removed
 *
 * @error: If allocation fails, returns a NULL t_dstr.
 * @args: If str->s is NULL, returns a NULL t_dstr.
 * 		  If remove_str.s is NULL or empty, returns a copy of str.
 * @infos: The input string is freed regardless of success or failure.
 */
t_dstr	str_dremove(
	t_dstr *str,
	t_cstr remove_str)
{
	t_dstr	res;
	t_cstr	str_;
	t_cstr	match;
	t_dstr	sub_str;

	if (str->s == NULL)
		return (free_dstr(str), dstr_s(0));
	if (remove_str.s == NULL || remove_str.len == 0)
		return (res = dstr_d(*str), free_dstr(str), res);
	res = dstr_s(1);
	str_ = cstr_d(*str);
	while (str_.len > 0)
	{
		match = str_findsub(str_, remove_str);
		sub_str = get_next_sub_string(str_, match);
		if (sub_str.s == NULL)
			return (free_dstr(&res), free_dstr(str), dstr_s(0));
		res = str_insert(&res, &sub_str, res.len);
		if (res.s == NULL)
			return (free_dstr(&res), free_dstr(&sub_str), free_dstr(str), res);
		str_ = str_shift_(str_, match, remove_str);
	}
	return (free_dstr(str), res);
}
