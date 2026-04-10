/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dstr_arr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 11:21:31 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/29 11:28:18 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_string.h"

/**
 * dstr_arr - Creates an array structure of t_dstr from an array strings
 *
 * @param strs An array of strings
 * @param count The number of strings in the array
 * @return A t_dstr_arr containing an array of t_dstr structures
 *
 * @args: If strs is NULL or count is 0, returns a NULL t_dstr_arr.
 * @error: If allocation fails, returns a NULL t_dstr_arr (errno ENOMEM).
 */
t_dstr_arr	dstr_arr(t_i8 **strs, size_t count)
{
	size_t		i;
	t_dstr		str;
	t_dstr_arr	res;

	if (strs == NULL || count == 0)
		return (res.strs = NULL, res.len = 0, res.size = 0, res);
	res.strs = malloc(sizeof(t_dstr) * count);
	if (res.strs == NULL)
		return (res.strs = NULL, res.len = 0, res.size = 0, res);
	i = 0;
	while (i < count)
	{
		str = dstr_c(cstr(strs[i]));
		if (str.s == NULL)
			return (free_dstr_arr(&res), res.strs = NULL, res.len = 0, res);
		res.strs[i] = str;
		++i;
	}
	res.len = count;
	res.size = count;
	return (res);
}

/**
 * dstr_arr_s - Creates an empty array structure of t_dstr
 *
 * @param count The number of t_dstr structures to allocate
 * @return A t_dstr_arr containing an array of t_dstr structures
 *
 * @args: If count is 0, returns a NULL t_dstr_arr.
 * @error: If allocation fails, returns a NULL t_dstr_arr (errno ENOMEM).
 */
t_dstr_arr	dstr_arr_s(size_t count)
{
	t_dstr_arr	res;

	if (count == 0)
		return (res.strs = NULL, res.len = 0, res.size = 0, res);
	res.strs = malloc(sizeof(t_dstr) * count);
	if (res.strs == NULL)
		return (res.strs = NULL, res.len = 0, res.size = 0, res);
	res.len = 0;
	res.size = count;
	return (res);
}

/**
 * dstr_arr_d - Duplicates a dynamic string array structure
 *
 * @param arr The t_dstr_arr structure to duplicate
 * @return A new t_dstr_arr containing a copy of the array
 *
 * @args: If arr->strs is NULL, returns a NULL t_dstr_arr.
 * @error: If allocation fails, returns a NULL t_dstr_arr (errno ENOMEM).
 */
t_dstr_arr	dstr_arr_d(t_dstr_arr arr)
{
	size_t		i;
	t_dstr_arr	res;

	if (arr.strs == NULL)
		return (res = dstr_arr(NULL, 0), res);
	res = dstr_arr_s(arr.size);
	if (res.strs == NULL)
		return (res);
	i = 0;
	while (i < arr.len)
	{
		res.strs[i] = dstr_d(arr.strs[i]);
		if (res.strs[i].s == NULL)
			return (free_dstr_arr(&res), res);
		++i;
	}
	res.len = arr.len;
	return (res);
}
