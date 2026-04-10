/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:19:11 by adouieb           #+#    #+#             */
/*   Updated: 2026/02/05 21:49:12 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_string.h"

/**
 * add_to_str_arr - Add a substring to a t_dstr_arr
 *
 * @param res The t_dstr_arr to add to
 * @param str The original string to extract from
 * @param start The starting index of the substring
 * @param len The length of the substring
 * @return The updated t_dstr_arr
 *
 * @error: If allocation fails, frees the array and returns NULL.
 */
static t_dstr_arr	*add_to_str_arr(
	t_dstr_arr *res,
	t_cstr str,
	size_t start,
	size_t len)
{
	t_dstr	sub_str;

	sub_str = str_sub(str, (t_u32)start, len);
	if (sub_str.s == NULL)
		return (free_dstr_arr(res), NULL);
	*res = str_arr_add_d(res, sub_str);
	if (res->strs == NULL)
		return (free_dstr(&sub_str), NULL);
	return (res);
}

/**
 * str_split_ - Splits a string into substrings based on a delimiter
 *
 * @param res The t_dstr_arr to store the resulting substrings
 * @param str The t_cstr structure to split
 * @param c The delimiter character
 * @return The buffer with split substrings
 *
 * @error: If allocation fails, returns a NULL t_dbuf (errno ENOMEM).
 */
static t_dstr_arr	str_split_(
	t_dstr_arr res,
	t_cstr str,
	t_i8 c,
	t_bool (*rule)(t_cstr, t_i8, t_u32))
{
	size_t	i;
	size_t	j;
	t_i32	start;
	size_t	str_len;

	1 && (i = 0, j = 0, start = -1);
	while (j < res.size && i <= str.len)
	{
		if (str.s[i] != c && start == -1)
			start = (t_i32)i;
		else if ((str.s[i] == c || i == str.len) && start != -1)
		{
			if (rule == NULL || rule(str, c, (t_u32)i) == TRUE)
			{
				str_len = i - (size_t)start;
				if (add_to_str_arr(&res, str, (size_t)start, str_len) == NULL)
					return (free_dstr_arr(&res), res);
				1 && (++j, start = -1);
			}
		}
		++i;
	}
	return (res);
}

/**
 * str_count_words - Counts the words in a string separated by a delimiter
 *
 * @param str The t_cstr structure to count words in
 * @param c The delimiter character
 * @return The number of words found
 */
static t_u32	str_count_words(
	t_cstr str,
	t_i8 c,
	t_bool (*rule)(t_cstr, t_i8, t_u32))
{
	size_t	i;
	t_u32	count;
	t_bool	in_word;

	1 && (i = 0, count = 0, in_word = FALSE);
	while (i < str.len)
	{
		if (str.s[i] != c && in_word == FALSE)
			1 && (++count, in_word = TRUE);
		else if (str.s[i] == c && in_word == TRUE)
		{
			if (rule == NULL || rule(str, c, (t_u32)i) == TRUE)
				in_word = FALSE;
		}
		++i;
	}
	return (count);
}

/**
 * str_split - Splits a string into an array of substrings using a delimiter
 *
 * @param str The t_cstr structure to split
 * @param c The delimiter character
 * @param rule Optional rule function to determine splitting behavior
 * @return A t_dstr_arr containing an array of t_dstr substrings
 *
 * @args: If str.s is NULL, returns a NULL array (strs == NULL).
 * @error: If allocation fails, returns a NULL t_dstr_arr (errno ENOMEM).
 * @info: If the split yields no words (e.g., empty string or string contains
 *        only delimiters), returns an array with a single empty t_dstr.
 */
t_dstr_arr	str_split(
	t_cstr str,
	t_i8 c,
	t_bool (*rule)(t_cstr, t_i8, t_u32))
{
	t_dstr_arr	res;
	t_u32		word_count;

	if (str.s == NULL)
		return (dstr_arr(NULL, 0));
	word_count = str_count_words(str, c, rule);
	if (word_count == 0)
	{
		res = dstr_arr_s(1);
		if (res.strs == NULL)
			return (res);
		res = str_arr_add_d(&res, dstr_s(0));
		return (res);
	}
	res = dstr_arr_s(word_count);
	if (res.strs == NULL)
		return (res);
	res = str_split_(res, str, c, rule);
	return (res);
}
