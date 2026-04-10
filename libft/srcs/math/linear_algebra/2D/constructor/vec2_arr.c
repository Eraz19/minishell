/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_arr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 11:36:20 by adouieb           #+#    #+#             */
/*   Updated: 2026/03/17 19:18:47 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"

/**
 * vec2_arr_s - Creates an array structure of t_vec2 with no vectors
 *
 * @param size The number of t_vec2 structures to allocate
 * @return A t_vec2_arr containing an array of t_vec2 structures
 *
 * @args: If size is 0, returns a NULL t_vec2_arr.
 * @error: If allocation fails, returns a NULL t_vec2_arr (errno ENOMEM).
 */
t_vec2_arr	vec2_arr_s(size_t size)
{
	t_vec2_arr	res;

	if (size == 0)
		return (res.vecs = NULL, res.len = 0, res.size = 0, res);
	res.vecs = malloc(size * sizeof(t_vec2));
	if (res.vecs == NULL)
		return (res.vecs = NULL, res.len = 0, res.size = 0, res);
	res.len = 0;
	res.size = size;
	return (res);
}

/**
 * vec2_arr_v - Duplicates an array structure of t_vec2
 *
 * @param arr The array of t_vec2 structures to copy
 * @return A t_vec2_arr containing a copy of the input array
 *
 * @args: If arr->vecs is NULL, returns a NULL t_vec2_arr.
 * @error: If allocation fails, returns a NULL t_vec2_arr (errno ENOMEM).
 */
t_vec2_arr	vec2_arr_v(t_vec2_arr arr)
{
	size_t		i;
	t_vec2_arr	res;

	if (arr.vecs == NULL)
		return (vec2_arr_s(0));
	res = vec2_arr_s(arr.size);
	if (res.vecs == NULL)
		return (res);
	i = 0;
	while (i < arr.len)
	{
		res.vecs[i].vec_u = vec2_u32(arr.vecs[i].vec_u.x, arr.vecs[i].vec_u.y);
		++i;
	}
	res.len = arr.len;
	return (res);
}
