/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cross_product.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 11:54:56 by adouieb           #+#    #+#             */
/*   Updated: 2026/03/17 19:40:29 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"
#include "libft_types.h"

/**
 * vec3_cross_product_i32 - Computes the cross product of two t_vec3_i32
 *
 * @param vec1 The first 3D integer vector
 * @param vec2 The second 3D integer vector
 * @return The cross product as a t_vec3_i32
 *
 * @infos: The cross product of two 3D vectors results in a 3D vector
 *			perpendicular to both input vector and has a magnitude equal to the
 *			area of the parallelogram formed by the two vectors.
 */
t_vec3_i32	vec3_cross_product_i32(t_vec3_i32 vec1, t_vec3_i32 vec2)
{
	return (
		vec3_i32(
			vec1.y * vec2.z - vec1.z * vec2.y,
			vec1.z * vec2.x - vec1.x * vec2.z,
			vec1.x * vec2.y - vec1.y * vec2.x)
	);
}

/**
 * vec3_cross_product_u32 - Computes the cross product of two t_vec3_u32
 *
 * @param vec1 The first 3D unsigned integer vector
 * @param vec2 The second 3D unsigned integer vector
 * @return The cross product as a t_vec3_i32
 *
 * @infos: The cross product of two 3D vectors results in a 3D vector
 *			perpendicular to both input vector and has a magnitude equal to the
 *			area of the parallelogram formed by the two vectors.
 */
t_vec3_i32	vec3_cross_product_u32(t_vec3_u32 vec1, t_vec3_u32 vec2)
{
	return (
		vec3_i32(
			(t_i32)(vec1.y * vec2.z) - (t_i32)(vec1.z * vec2.y),
			(t_i32)(vec1.z * vec2.x) - (t_i32)(vec1.x * vec2.z),
			(t_i32)(vec1.x * vec2.y) - (t_i32)(vec1.y * vec2.x))
	);
}

/**
 * vec3_cross_product_f32 - Computes the cross product of two t_vec3_f32
 *
 * @param vec1 The first 3D float vector
 * @param vec2 The second 3D float vector
 * @return The cross product as a t_vec3_f32
 *
 * @infos: The cross product of two 3D vectors results in a 3D vector
 *			perpendicular to both input vector and has a magnitude equal to the
 *			area of the parallelogram formed by the two vectors.
 */
t_vec3_f32	vec3_cross_product_f32(t_vec3_f32 vec1, t_vec3_f32 vec2)
{
	return (
		vec3_f32(
			vec1.y * vec2.z - vec1.z * vec2.y,
			vec1.z * vec2.x - vec1.x * vec2.z,
			vec1.x * vec2.y - vec1.y * vec2.x)
	);
}
