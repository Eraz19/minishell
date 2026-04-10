/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstr_arr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 11:26:02 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/29 11:28:30 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_string.h"

/**
 * cstr_arr - Creates an array structure of t_cstr from an array strings
 *
 * @param strs An array of constant strings
 * @param count The number of strings in the array
 * @return A t_cstr_arr containing an array of t_cstr structures
 *
 * @args: If strs is NULL or count is 0, returns a NULL t_dbuf.
 * @error: If allocation fails, returns a NULL t_cstr_arr (errno ENOMEM).
 */
t_cstr_arr	cstr_arr(const t_i8 **strs, size_t count)
{
	size_t		i;
	t_cstr_arr	res;

	if (strs == NULL || count == 0)
		return (res.strs = NULL, res.len = 0, res.size = 0, res);
	res.strs = malloc(sizeof(t_cstr) * count);
	if (res.strs == NULL)
		return (res.strs = NULL, res.len = 0, res.size = 0, res);
	i = 0;
	while (i < count)
		1 && (res.strs[i] = cstr(strs[i]), ++i);
	res.len = count;
	res.size = count;
	return (res);
}

/**
 * cstr_arr_s - Creates an empty t_cstr_arr with a specified size
 *
 * @param count The number of t_cstr elements to allocate
 * @return A t_cstr_arr with allocated space for 'count' t_cstr elements
 *
 * @args: If count = 0, returns a NULL t_cstr_arr.
 * @error: If allocation fails, returns a NULL t_cstr_arr (errno ENOMEM).
 */
t_cstr_arr	cstr_arr_s(size_t count)
{
	t_cstr_arr	res;

	if (count == 0)
		return (res.strs = NULL, res.len = 0, res.size = 0, res);
	res.strs = malloc(sizeof(t_cstr) * count);
	if (res.strs == NULL)
		return (res.strs = NULL, res.len = 0, res.size = 0, res);
	res.len = 0;
	res.size = count;
	return (res);
}

/**
 * cstr_arr_c - Duplicates a constant string array structure
 *
 * @param arr The t_cstr_arr to duplicate
 * @return A new t_cstr_arr containing copies of the t_cstr elements
 *
 * @args: If arr.strs is NULL or arr.len is 0, returns a NULL t_cstr_arr.
 * @error: If allocation fails, returns a NULL t_cstr_arr (errno ENOMEM).
 */
t_cstr_arr	cstr_arr_c(t_cstr_arr arr)
{
	size_t		i;
	t_cstr_arr	res;

	if (arr.strs == NULL || arr.len == 0)
		return (res.strs = NULL, res.len = 0, res.size = 0, res);
	res.strs = malloc(sizeof(t_cstr) * arr.len);
	if (res.strs == NULL)
		return (res.strs = NULL, res.len = 0, res.size = 0, res);
	i = 0;
	while (i < arr.len)
		1 && (res.strs[i] = arr.strs[i], ++i);
	res.len = arr.len;
	res.size = arr.len;
	return (res);
}
