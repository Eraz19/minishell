/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 15:21:12 by adouieb           #+#    #+#             */
/*   Updated: 2026/02/19 17:55:16 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"
#include "libft_types.h"

/**
 * vec3_add_i32 - Adds two t_vec3_i32 vectors
 *
 * @param vec1 The first 3D integer vector
 * @param vec2 The second 3D integer vector
 * @return The resulting vector of the addition
 *
 * @infos: The addition of two vectors applies a translation to the first vector
 *			by the second vector.
 */
t_vec3_i32	vec3_add_i32(t_vec3_i32 vec1, t_vec3_i32 vec2)
{
	return (vec3_i32(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z));
}

/**
 * vec3_add_u32 - Adds two t_vec3_u32 vectors
 *
 * @param vec1 The first 3D unsigned integer vector
 * @param vec2 The second 3D unsigned integer vector
 * @return The resulting vector of the addition
 *
 * @infos: The addition of two vectors applies a translation to the first vector
 *			by the second vector.
 */
t_vec3_u32	vec3_add_u32(t_vec3_u32 vec1, t_vec3_u32 vec2)
{
	return (vec3_u32(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z));
}

/**
 * vec3_add_f32 - Adds two t_vec3_f32 vectors
 *
 * @param vec1 The first 3D float vector
 * @param vec2 The second 3D float vector
 * @return The resulting vector of the addition
 *
 * @infos: The addition of two vectors applies a translation to the first vector
 *			by the second vector.
 */
t_vec3_f32	vec3_add_f32(t_vec3_f32 vec1, t_vec3_f32 vec2)
{
	return (vec3_f32(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z));
}
