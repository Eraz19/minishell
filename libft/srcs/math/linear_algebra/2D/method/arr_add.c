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
 * vec2_arr_add_v - Adds a t_vec2 to a t_vec2_arr
 *
 * MEMORY OWNERSHIP: This function always consumes (frees) 'arr' if a
 * reallocation is needed to accommodate the new vector.
 * The original 'arr' pointer becomes invalid if a reallocation occurs.
 * Always reassign the result:
 *     arr = vec2_arr_add_v(&arr, vec_to_add); // ✓ Correct usage
 *
 * @param arr The pointer to the t_vec2_arr to add to (freed if realloc)
 * @param vec The t_vec2 to add to the array
 * @return A t_vec2_arr with the added vector
 *
 * @error: If allocation fails, returns a NULL t_vec2_arr (errno ENOMEM).
 */
t_vec2_arr	vec2_arr_add_v(t_vec2_arr *arr, t_vec2 vec)
{
	size_t		i;
	t_vec2_arr	res;

	if (arr->len + 1 > arr->size)
	{
		res = vec2_arr_s(arr->size + 1);
		if (res.vecs == NULL)
			return (*arr);
		i = 0;
		while (i < arr->len)
			1 && (res.vecs[i] = arr->vecs[i], ++i);
		res.vecs[i] = vec;
		res.len = arr->len + 1;
		return (free_vec2_arr(arr), res);
	}
	arr->vecs[arr->len] = vec;
	return (arr->len += 1, *arr);
}
