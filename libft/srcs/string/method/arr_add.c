/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:43:04 by adouieb           #+#    #+#             */
/*   Updated: 2026/03/01 19:02:25 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_string.h"

/**
 * str_arr_add_d - Adds a dynamic string to a dynamic string array
 *
 * MEMORY OWNERSHIP: This function always consumes (frees) 'arr' if a
 * reallocation is needed to accommodate the new string.
 * The original 'arr' pointer becomes invalid if a reallocation occurs.
 * Always reassign the result:
 *     arr = str_arr_add_d(&arr, string_to_add); // ✓ Correct usage
 *
 * @param arr The pointer to the t_dstr_arr to add to (freed if realloc)
 * @param str The t_dstr to add to the array
 * @return A t_dstr_arr with the added string
 *
 * @error: If allocation fails, returns a NULL t_dstr_arr (errno ENOMEM).
 */
t_dstr_arr	str_arr_add_d(t_dstr_arr *arr, t_dstr str)
{
	size_t		i;
	t_dstr_arr	res;

	if (arr->len + 1 > arr->size)
	{
		res = dstr_arr_s(arr->size + 1);
		if (res.strs == NULL)
			return (free_dstr_arr(arr), res);
		i = 0;
		while (i < arr->len)
			1 && (res.strs[i] = arr->strs[i], ++i);
		res.strs[i] = str;
		res.len = arr->len + 1;
		res.size = arr->size + 1;
		free(arr->strs);
		arr->strs = NULL;
		arr->len = 0;
		return (res);
	}
	arr->strs[arr->len] = str;
	return (arr->len += 1, *arr);
}

/**
 * str_arr_realloc - Reallocates a dynamic string array if needed
 *
 * MEMORY OWNERSHIP: This function consumes (frees) the input 'arr', the
 * original 'arr' becomes invalid.
 * To keep a copy of the array, first duplicate it before.
 * Always reassign the result:
 *     t_dstr_arr arr_copy = dstr_arr_d(original_arr);
 *     arr_copy = str_arr_realloc(&arr_copy, new_size); // ✓ Correct usage
 *     original_arr                                     // ✓ remains valid
 *
 * @param arr The pointer to the t_dstr_arr to reallocate (always freed)
 * @param new_size The new size required
 * @return A new t_dstr_arr containing the reallocation of the original array
 *
 * @args: If new_size = 0, returns a NULL t_dstr_arr.
 * @error: If allocation fails, returns a NULL t_dstr_arr (errno ENOMEM).
 *
 */
static t_dstr_arr	str_arr_realloc(t_dstr_arr *arr, size_t new_size)
{
	size_t		i;
	t_dstr		str;
	t_dstr_arr	arr_;

	arr_ = dstr_arr_s(new_size);
	if (arr_.strs == NULL)
		return (free_dstr_arr(arr), arr_);
	i = 0;
	while (i < arr->len)
	{
		str = dstr_d(arr->strs[i]);
		if (str.s == NULL)
			return (free_dstr_arr(&arr_), free_dstr_arr(arr), arr_);
		arr_.strs[i++] = str;
	}
	return (arr_.len = arr->len, free_dstr_arr(arr), arr_);
}

/**
 * str_arr_add_d_arr - Adds a dynamic string array to another dynamic string
 * array
 *
 * MEMORY OWNERSHIP: This function always consumes (frees) 'add_arr' and the
 * t_dstr in it.
 * It also consumes (frees) 'arr' if a reallocation is needed to accommodate
 * the new content.
 * The original 'arr' becomes invalid if a reallocation occurs.
 * But the 'add_arr' always becomes invalid.
 * To keep a copy of the 'add_arr', first duplicate it before.
 * Always reassign the result:
 *     t_dstr_arr arr_copy = dstr_arr_d(original_arr);
 *     t_dstr_arr add_arr_copy = dstr_arr_d(add_arr);
 *     arr = str_arr_add_d_arr(&arr_copy, &add_arr_copy); // ✓ Correct
 *     original_arr                                       // ✓ remains valid
 *     add_arr                                            // ✓ remains valid
 *
 * @param arr The pointer to the t_dstr_arr to add to (freed if realloc)
 * @param add_arr The pointer to the t_dstr_arr to add from (always freed)
 * @return A t_dstr_arr with the added strings
 *
 * @args: If both add_arr is NULL or empty, returns a unchanged t_dstr_arr.
 * @error: If allocation fails, returns a NULL t_dstr_arr (errno ENOMEM).
 */
t_dstr_arr	str_arr_add_d_arr(t_dstr_arr *arr, t_dstr_arr *add_arr)
{
	size_t		i;
	t_dstr		str;

	if (add_arr == NULL || add_arr->strs == NULL || add_arr->len == 0)
		return (*arr);
	if (arr->len + add_arr->len > arr->size)
		*arr = str_arr_realloc(arr, arr->len + add_arr->len);
	if (arr->strs == NULL)
		return (free_dstr_arr(add_arr), *arr);
	i = 0;
	while (i < add_arr->len)
	{
		str = dstr_d(add_arr->strs[i]);
		if (str.s == NULL)
			return (free_dstr_arr(add_arr), free_dstr_arr(arr), *arr);
		arr->strs[arr->len + i] = str;
		++i;
	}
	return (arr->len += add_arr->len, free_dstr_arr(add_arr), *arr);
}

/**
 * str_arr_add_c - Adds a constant string to a constant string array
 *
 * MEMORY OWNERSHIP: This function always consumes (frees) 'arr' if a
 * reallocation is needed to accommodate the new string.
 * The original 'arr' pointer becomes invalid if a reallocation occurs.
 * Always reassign the result:
 *     arr = str_arr_add_c(&arr, string_to_add); // ✓ Correct usage
 *
 * @param arr The pointer to the t_cstr_arr to add to (freed if realloc)
 * @param str The t_cstr to add to the array
 * @return A t_cstr_arr with the added string
 *
 * @error: If allocation fails, returns a NULL t_cstr_arr (errno ENOMEM).
 */
t_cstr_arr	str_arr_add_c(t_cstr_arr *arr, t_cstr str)
{
	size_t		i;
	t_cstr_arr	res;

	if (arr->len + 1 > arr->size)
	{
		res = cstr_arr_s(arr->size + 1);
		if (res.strs == NULL)
			return (free_cstr_arr(arr), res);
		i = 0;
		while (i < arr->len)
			1 && (res.strs[i] = arr->strs[i], ++i);
		res.strs[i] = str;
		res.len = arr->len + 1;
		res.size = arr->size + 1;
		return (free_cstr_arr(arr), res);
	}
	arr->strs[arr->len] = str;
	return (arr->len += 1, *arr);
}

/**
 * str_arr_add_c_arr - Adds a constant string array to another constant string
 * array
 *
 * MEMORY OWNERSHIP: This function always consumes (frees) 'add_arr'.
 * It also consumes (frees) 'arr' if a reallocation is needed to accommodate
 * the new content.
 * The original 'arr' becomes invalid if a reallocation occurs.
 * But the 'add_arr' always becomes invalid.
 * To keep a copy of the 'add_arr', first duplicate it before.
 * Always reassign the result:
 *     t_cstr_arr arr_copy = cstr_arr_c(original_arr);
 *     t_cstr_arr add_arr_copy = cstr_arr_c(add_arr);
 *     arr = str_arr_add_c_arr(&arr_copy, &add_arr_copy); // ✓ Correct
 *     original_arr                                       // ✓ remains valid
 *     add_arr                                            // ✓ remains valid
 *
 * @param arr The pointer to the t_cstr_arr to add to (freed if realloc)
 * @param add_arr The pointer to the t_cstr_arr to add from (always freed)
 * @return A t_cstr_arr with the added strings
 *
 * @args: If both add_arr is NULL or empty, returns a unchanged t_cstr_arr.
 * @error: If allocation fails, returns a NULL t_cstr_arr (errno ENOMEM).
 */
t_cstr_arr	str_arr_add_c_arr(t_cstr_arr *arr, t_cstr_arr *add_arr)
{
	size_t		i;
	t_cstr_arr	res;

	if (add_arr == NULL || add_arr->strs == NULL || add_arr->len == 0)
		return (*arr);
	if (arr->len + add_arr->len > arr->size)
	{
		res = cstr_arr_s(arr->len + add_arr->len);
		if (res.strs == NULL)
			return (free_cstr_arr(arr), res);
		i = 0;
		while (i < arr->len)
			1 && (res.strs[i] = arr->strs[i], ++i);
		while (i < arr->len + add_arr->len)
			1 && (res.strs[i] = add_arr->strs[i - arr->len], ++i);
		res.len = arr->len + add_arr->len;
		res.size = arr->len + add_arr->len;
		return (free_cstr_arr(arr), free_cstr_arr(add_arr), res);
	}
	i = 0;
	while (i < add_arr->len)
		1 && (arr->strs[arr->len + i] = add_arr->strs[i], ++i);
	arr->len += add_arr->len;
	return (free_cstr_arr(add_arr), *arr);
}
