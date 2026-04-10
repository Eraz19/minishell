/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substract.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 09:37:13 by adouieb           #+#    #+#             */
/*   Updated: 2026/03/17 19:39:17 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"
#include "libft_types.h"

/**
 * vec3_sub_i32 - Substracts two t_vec3_i32 vectors
 *
 * @param vec1 The first 3D integer vector
 * @param vec2 The second 3D integer vector
 * @return The resulting vector of the subtraction
 *
 * @infos: The subtraction of two vectors applies a translation to the first
 *			vector by the negative of the second vector.
 */
t_vec3_i32	vec3_sub_i32(t_vec3_i32 vec1, t_vec3_i32 vec2)
{
	return (vec3_i32(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z));
}

/**
 * vec3_sub_u32 - Substracts two t_vec3_u32 vectors
 *
 * @param vec1 The first 3D unsigned integer vector
 * @param vec2 The second 3D unsigned integer vector
 * @return The resulting vector of the subtraction
 *
 * @infos: The subtraction of two vectors applies a translation to the first
 *			vector by the negative of the second vector.
 */
t_vec3_i32	vec3_sub_u32(t_vec3_u32 vec1, t_vec3_u32 vec2)
{
	return (
		vec3_i32(
			(t_i32)vec1.x - (t_i32)vec2.x,
			(t_i32)vec1.y - (t_i32)vec2.y,
			(t_i32)vec1.z - (t_i32)vec2.z)
	);
}

/**
 * vec3_sub_f32 - Substracts two t_vec3_f32 vectors
 *
 * @param vec1 The first 3D float vector
 * @param vec2 The second 3D float vector
 * @return The resulting vector of the subtraction
 *
 * @infos: The subtraction of two vectors applies a translation to the first
 *			vector by the negative of the second vector.
 */
t_vec3_f32	vec3_sub_f32(t_vec3_f32 vec1, t_vec3_f32 vec2)
{
	return (vec3_f32(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z));
}
