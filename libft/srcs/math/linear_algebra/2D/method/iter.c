/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 18:08:47 by adouieb           #+#    #+#             */
/*   Updated: 2026/02/19 18:26:57 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"

/**
 * vec2_arr_map - Applies a function to each vector2 to create a new array
 *
 * MEMORY OWNERSHIP: This function consumes (frees) the input 'arr', the
 * original 'arr' becomes invalid.
 * To keep a copy of the array, first duplicate it before.
 * Always reassign the result:
 *     t_vec2_arr arr_copy = vec2_arr_d(original_arr);
 *     arr_copy = vec2_arr_map(&arr_copy, func, extra); // ✓ Correct usage
 *     original_arr                                     // ✓ remains valid
 *
 * @param arr The pointer to the t_vec2_arr to map over (always freed)
 * @param f The function to apply to each t_vec2 (with index)
 * @return A new t_vec2_arr with the transformed vectors
 *
 * @args: If arr->vecs is NULL or f is NULL, returns a NULL t_vec2_arr.
 * @error: If allocation fails, returns a NULL t_vec2_arr (errno ENOMEM).
 */
t_vec2_arr	vec2_arr_map(
	t_vec2_arr *arr,
	t_vec2 (*f)(t_u32, t_vec2, void*),
	void *extra)
{
	size_t		i;
	t_vec2_arr	res;

	i = 0;
	if (arr->vecs == NULL || f == NULL)
		return (free_vec2_arr(arr), vec2_arr_s(0));
	res = vec2_arr_s(arr->size);
	if (res.vecs == NULL)
		return (free_vec2_arr(arr), res);
	while (i < arr->len)
	{
		if (extra == NULL)
			res.vecs[i] = f((t_u32)i, arr->vecs[i], NULL);
		else
			res.vecs[i] = f((t_u32)i, arr->vecs[i], extra);
		++i;
	}
	res.len = arr->len;
	free_vec2_arr(arr);
	return (res);
}
