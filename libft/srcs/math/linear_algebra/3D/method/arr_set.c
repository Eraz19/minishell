/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 17:30:45 by adouieb           #+#    #+#             */
/*   Updated: 2026/03/17 19:18:47 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"

/**
 * vec3_arr_set_v - Set a t_vec3 to a t_vec3_arr at the specified index.
 *
 * MEMORY OWNERSHIP: This function always consumes (frees) 'arr' if a
 * reallocation is needed to accommodate the new vector.
 * The original 'arr' pointer becomes invalid if a reallocation occurs.
 * Always reassign the result:
 *     arr = vec3_arr_add_v(&arr, vec_to_add); // ✓ Correct usage
 *
 * @param arr The pointer to the t_vec3_arr to add to (freed if realloc)
 * @param vec The t_vec3 to add to the array
 * @param index The index at which to set the vector
 * @return A t_vec3_arr with the added vector
 *
 * @error: If allocation fails, returns a NULL t_vec3_arr (errno ENOMEM).
 */
t_vec3_arr	vec3_arr_set_v(t_vec3_arr *arr, t_vec3 vec, size_t index)
{
	size_t		i;
	t_vec3_arr	res;

	if (index >= arr->len)
		return (*arr);
	if (arr->len + 1 > arr->size)
	{
		res = vec3_arr_s(arr->size + 1);
		if (res.vecs == NULL)
			return (free_vec3_arr(arr), res);
		i = 0;
		while (i < index)
			1 && (res.vecs[i] = arr->vecs[i], ++i);
		res.vecs[i] = vec;
		while (i < arr->len)
			1 && (res.vecs[i + 1] = arr->vecs[i], ++i);
		res.len = arr->len + 1;
		return (free_vec3_arr(arr), res);
	}
	arr->vecs[index] = vec;
	return (arr->len += 1, *arr);
}
