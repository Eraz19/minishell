/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 11:11:04 by adouieb           #+#    #+#             */
/*   Updated: 2026/03/17 19:36:15 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"
#include "libft_types.h"

/**
 * vec4_normalize_i32 - Normalizes a t_vec4_i32 to become a unit vector 
 *
 * @param vec The 4D vector to normalize
 * @return The normalized 4D vector as a t_vec4_f32
 *
 * @info: If the norm of the vector is zero, returns a zero t_vec4_f32.  
 */
t_vec4_f32	vec4_normalize_i32(t_vec4_i32 vec)
{
	t_f32	vec_norm;

	vec_norm = vec4_norm_i32(vec);
	if (vec_norm == 0)
		return (vec4_f32(0, 0, 0, 0));
	return (
		vec4_f32(
			(t_f32)vec.x / vec_norm,
			(t_f32)vec.y / vec_norm,
			(t_f32)vec.z / vec_norm,
			(t_f32)vec.w / vec_norm)
	);
}

/**
 * vec4_normalize_u32 - Normalizes a t_vec4_u32 to become a unit vector 
 *
 * @param vec The 4D vector to normalize
 * @return The normalized 4D vector as a t_vec4_f32
 *
 * @info: If the norm of the vector is zero, returns a zero t_vec4_f32.  
 */
t_vec4_f32	vec4_normalize_u32(t_vec4_u32 vec)
{
	t_f32	vec_norm;

	vec_norm = vec4_norm_u32(vec);
	if (vec_norm == 0)
		return (vec4_f32(0, 0, 0, 0));
	return (
		vec4_f32(
			(t_f32)vec.x / vec_norm,
			(t_f32)vec.y / vec_norm,
			(t_f32)vec.z / vec_norm,
			(t_f32)vec.w / vec_norm)
	);
}

/**
 * vec4_normalize_f32 - Normalizes a t_vec4_f32 to become a unit vector 
 *
 * @param vec The 4D vector to normalize
 * @return The normalized 4D vector as a t_vec4_f32
 *
 * @info: If the norm of the vector is zero, returns a zero t_vec4_f32.  
 */
t_vec4_f32	vec4_normalize_f32(t_vec4_f32 vec)
{
	t_f32	vec_norm;

	vec_norm = vec4_norm_f32(vec);
	if (vec_norm == 0)
		return (vec4_f32(0, 0, 0, 0));
	return (
		vec4_f32(
			(t_f32)vec.x / vec_norm,
			(t_f32)vec.y / vec_norm,
			(t_f32)vec.z / vec_norm,
			(t_f32)vec.w / vec_norm)
	);
}
