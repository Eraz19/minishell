/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 17:30:45 by adouieb           #+#    #+#             */
/*   Updated: 2026/03/17 19:18:47 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"

/**
 * vec3_arr_add_v - Adds a t_vec3 to a t_vec3_arr
 *
 * MEMORY OWNERSHIP: This function always consumes (frees) 'arr' if a
 * reallocation is needed to accommodate the new vector.
 * The original 'arr' pointer becomes invalid if a reallocation occurs.
 * Always reassign the result:
 *     arr = vec3_arr_add_v(&arr, vec_to_add); // ✓ Correct usage
 *
 * @param arr The pointer to the t_vec3_arr to add to (freed if realloc)
 * @param vec The t_vec3 to add to the array
 * @return A t_vec3_arr with the added vector
 *
 * @error: If allocation fails, returns a NULL t_vec3_arr (errno ENOMEM).
 */
t_vec3_arr	vec3_arr_add_v(t_vec3_arr *arr, t_vec3 vec)
{
	size_t		i;
	t_vec3_arr	res;

	if (arr->len + 1 > arr->size)
	{
		res = vec3_arr_s(arr->size + 1);
		if (res.vecs == NULL)
			return (*arr);
		i = 0;
		while (i < arr->len)
			1 && (res.vecs[i] = arr->vecs[i], ++i);
		res.vecs[i] = vec;
		res.len = arr->len + 1;
		return (free_vec3_arr(arr), res);
	}
	arr->vecs[arr->len] = vec;
	return (arr->len += 1, *arr);
}

/**
 * vec3_arr_add_arr - Adds a t_vec3_arr to another t_vec3_arr
 *
 * MEMORY OWNERSHIP: This function always consumes (frees) 'vec'.
 * It also consumes (frees) 'arr' if a reallocation is needed to accommodate
 * the new vector.
 * The original 'arr' pointer becomes invalid if a reallocation occurs.
 * Always reassign the result:
 *     t_vec3_arr vec_copy = vec3_arr_v(original_arr);
 *     t_vec3_arr insert_arr = vec3_arr_v(vec_to_insert);
 *     vec_copy = vec3_arr_add_arr(&vec_copy, &insert_arr); // ✓ Correct usage
 *     original_arr                                         // ✓ remains valid
 *     vec_to_insert                                        // ✓ remains valid
 *
 * @param arr The pointer to the t_vec3_arr to add to (freed if realloc)
 * @param vec The t_vec3_arr to add to the array (always freed)
 * @return A t_vec3_arr with the added vector array
 *
 * @error: If allocation fails, returns a NULL t_vec3_arr (errno ENOMEM).
 */
t_vec3_arr	vec3_arr_add_arr(t_vec3_arr *arr, t_vec3_arr *vec)
{
	size_t		i;
	t_vec3_arr	res;

	if (arr->len + vec->len > arr->size)
	{
		res = vec3_arr_s(arr->size + vec->len);
		if (res.vecs == NULL)
			return (free_vec3_arr(vec), *arr);
		i = 0;
		while (i < arr->len)
			1 && (res.vecs[i] = arr->vecs[i], ++i);
		while (i < arr->len + vec->len)
			1 && (res.vecs[i] = vec->vecs[i - arr->len], ++i);
		res.len = arr->len + vec->len;
		return (free_vec3_arr(arr), free_vec3_arr(vec), res);
	}
	i = 0;
	while (i < vec->len)
		1 && (arr->vecs[arr->len + i] = vec->vecs[i], ++i);
	return (arr->len += vec->len, *arr);
}
