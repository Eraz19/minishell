/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 11:05:57 by adouieb           #+#    #+#             */
/*   Updated: 2026/03/17 19:38:49 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"
#include "libft_types.h"

/**
 * vec3_normalize_i32 - Normalizes a t_vec3_i32 to become a unit vector 
 *
 * @param vec The 3D vector to normalize
 * @return The normalized 3D vector as a t_vec3_f32
 *
 * @info: If the norm of the vector is zero, returns a zero t_vec3_f32.  
 */
t_vec3_f32	vec3_normalize_i32(t_vec3_i32 vec)
{
	t_f32	vec_norm;

	vec_norm = vec3_norm_i32(vec);
	if (vec_norm == 0)
		return (vec3_f32(0, 0, 0));
	return (
		vec3_f32(
			(t_f32)vec.x / vec_norm,
			(t_f32)vec.y / vec_norm,
			(t_f32)vec.z / vec_norm)
	);
}

/**
 * vec3_normalize_u32 - Normalizes a t_vec3_u32 to become a unit vector 
 *
 * @param vec The 3D vector to normalize
 * @return The normalized 3D vector as a t_vec3_f32
 *
 * @info: If the norm of the vector is zero, returns a zero t_vec3_f32.  
 */
t_vec3_f32	vec3_normalize_u32(t_vec3_u32 vec)
{
	t_f32	vec_norm;

	vec_norm = vec3_norm_u32(vec);
	if (vec_norm == 0)
		return (vec3_f32(0, 0, 0));
	return (
		vec3_f32(
			(t_f32)vec.x / vec_norm,
			(t_f32)vec.y / vec_norm,
			(t_f32)vec.z / vec_norm)
	);
}

/**
 * vec3_normalize_f32 - Normalizes a t_vec3_f32 to become a unit vector 
 *
 * @param vec The 3D vector to normalize
 * @return The normalized 3D vector as a t_vec3_f32
 *
 * @info: If the norm of the vector is zero, returns a zero t_vec3_f32.  
 */
t_vec3_f32	vec3_normalize_f32(t_vec3_f32 vec)
{
	t_f32	vec_norm;

	vec_norm = vec3_norm_f32(vec);
	if (vec_norm == 0)
		return (vec3_f32(0, 0, 0));
	return (vec3_f32(vec.x / vec_norm, vec.y / vec_norm, vec.z / vec_norm));
}
