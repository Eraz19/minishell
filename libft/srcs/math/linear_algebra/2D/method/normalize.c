/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 10:26:39 by adouieb           #+#    #+#             */
/*   Updated: 2026/03/17 19:36:46 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"
#include "libft_types.h"

/**
 * vec2_normalize_i32 - Normalizes a t_vec2_i32 to become a unit vector 
 *
 * @param vec The 2D vector to normalize
 * @return The normalized 2D vector as a t_vec2_f32
 *
 * @info: If the norm of the vector is zero, returns a zero t_vec2_f32.  
 */
t_vec2_f32	vec2_normalize_i32(t_vec2_i32 vec)
{
	t_f32	vec_norm;

	vec_norm = vec2_norm_i32(vec);
	if (vec_norm == 0)
		return ((t_vec2_f32){.x = 0, .y = 0});
	return (vec2_f32((t_f32)vec.x / vec_norm, (t_f32)vec.y / vec_norm));
}

/**
 * vec2_normalize_u32 - Normalizes a t_vec2_u32 to become a unit vector 
 *
 * @param vec The 2D vector to normalize
 * @return The normalized 2D vector as a t_vec2_f32
 *
 * @info: If the norm of the vector is zero, returns a zero t_vec2_f32.  
 */
t_vec2_f32	vec2_normalize_u32(t_vec2_u32 vec)
{
	t_f32	vec_norm;

	vec_norm = vec2_norm_u32(vec);
	if (vec_norm == 0)
		return ((t_vec2_f32){.x = 0, .y = 0});
	return (vec2_f32((t_f32)vec.x / vec_norm, (t_f32)vec.y / vec_norm));
}

/**
 * vec2_normalize_f32 - Normalizes a t_vec2_f32 to become a unit vector 
 *
 * @param vec The 2D vector to normalize
 * @return The normalized 2D vector as a t_vec2_f32
 *
 * @info: If the norm of the vector is zero, returns a zero t_vec2_f32.  
 */
t_vec2_f32	vec2_normalize_f32(t_vec2_f32 vec)
{
	t_f32	vec_norm;

	vec_norm = vec2_norm_f32(vec);
	if (vec_norm == 0)
		return ((t_vec2_f32){.x = 0, .y = 0});
	return (vec2_f32((t_f32)vec.x / vec_norm, (t_f32)vec.y / vec_norm));
}
