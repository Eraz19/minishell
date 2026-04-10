/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 18:59:15 by adouieb           #+#    #+#             */
/*   Updated: 2026/03/17 19:18:47 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"

/**
 * vec3_3_arr_filter - Filters a t_vec3_arr using a provided predicate function.
 *
 * MEMORY OWNERSHIP: This function consumes (frees) the input 'arr', the
 * original 'arr' becomes invalid.
 * To keep a copy of the array, first duplicate it before.
 * Always reassign the result:
 *     t_vec3_arr arr_copy = vec3_arr_v(original_arr);
 *     arr_copy = vec3_3_arr_filter(&arr_copy, func, extra); // ✓ Correct usage
 *     original_arr                                          // ✓ remains valid
 *
 * @param arr The pointer to the t_vec3_arr to filter (always freed)
 * @param f The function (predicate) to apply to each t_vec3 (with index)
 * @return A new t_vec3_arr with the filtered vectors
 *
 * @args: If arr->vecs is NULL or f is NULL, returns a NULL t_vec3_arr.
 * @error: If allocation fails, returns a NULL t_vec3_arr (errno ENOMEM).
 */
t_vec3_arr	vec3_3_arr_filter(
	t_vec3_arr *arr,
	t_bool (*f)(t_u32, t_vec3, void*),
	void *extra)
{
	size_t		i;
	size_t		len;
	t_vec3_arr	res;

	i = 0;
	len = 0;
	if (arr->vecs == NULL || f == NULL)
		return (free_vec3_arr(arr), vec3_arr_s(0));
	res = vec3_arr_s(arr->size);
	if (res.vecs == NULL)
		return (free_vec3_arr(arr), res);
	while (i < arr->len)
	{
		if (extra == NULL && f((t_u32)i, arr->vecs[i], NULL) == TRUE)
			1 && (res.vecs[len] = arr->vecs[i], ++len);
		else if (f((t_u32)i, arr->vecs[i], extra) == TRUE)
			1 && (res.vecs[len] = arr->vecs[i], ++len);
		++i;
	}
	res.len = len;
	free_vec3_arr(arr);
	return (res);
}
