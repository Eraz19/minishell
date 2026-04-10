/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_product.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 11:47:21 by adouieb           #+#    #+#             */
/*   Updated: 2026/02/19 09:43:49 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"
#include "libft_types.h"

/**
 * vec3_dot_product_i32 - Computes the dot product of two t_vec3_i32
 *
 * @param vec1 The first 3D integer vector
 * @param vec2 The second 3D integer vector
 * @return The dot product as an integer
 *
 * @infos: The dot product of two vectors results in a scalar value that
 *			represents by how much the first vector affects the second vector
 *			in terms of magnitude and direction.
 */
t_i32	vec3_dot_product_i32(t_vec3_i32 vec1, t_vec3_i32 vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

/**
 * vec3_dot_product_u32 - Computes the dot product of two t_vec3_u32
 *
 * @param vec1 The first 3D unsigned integer vector
 * @param vec2 The second 3D unsigned integer vector
 * @return The dot product as an unsigned integer
 *
 * @infos: The dot product of two vectors results in a scalar value that
 *			represents by how much the first vector affects the second vector
 *			in terms of magnitude and direction.
 */
t_u32	vec3_dot_product_u32(t_vec3_u32 vec1, t_vec3_u32 vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

/**
 * vec3_dot_product_f32 - Computes the dot product of two t_vec3_f32
 *
 * @param vec1 The first 3D float vector
 * @param vec2 The second 3D float vector
 * @return The dot product as a float
 *
 * @infos: The dot product of two vectors results in a scalar value that
 *			represents by how much the first vector affects the second vector
 *			in terms of magnitude and direction.
 */
t_f32	vec3_dot_product_f32(t_vec3_f32 vec1, t_vec3_f32 vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}
