/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cross_product.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 11:54:56 by adouieb           #+#    #+#             */
/*   Updated: 2026/03/09 13:15:25 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"
#include "libft_types.h"

/**
 * vec2_cross_product_i32 - Computes the cross product of two t_vec2_i32
 *
 * @param vec1 The first 2D integer vector
 * @param vec2 The second 2D integer vector
 * @return The cross product as a t_i32
 *
 * @infos: The cross product of two 2D vectors results in a scalar value
 *			that represents if the vectors are clockwise or counter-clockwise.
 */
t_i32	vec2_cross_product_i32(t_vec2_i32 vec1, t_vec2_i32 vec2)
{
	return (vec1.x * vec2.y - vec1.y * vec2.x);
}

/**
 * vec2_cross_product_u32 - Computes the cross product of two t_vec2_u32
 *
 * @param vec1 The first 2D unsigned integer vector
 * @param vec2 The second 2D unsigned integer vector
 * @return The cross product as a t_i32
 *
 * @infos: The cross product of two 2D vectors results in a scalar value
 *			that represents if the vectors are clockwise or counter-clockwise.
 */
t_i32	vec2_cross_product_u32(t_vec2_u32 vec1, t_vec2_u32 vec2)
{
	return ((t_i32)(vec1.x * vec2.y - vec1.y * vec2.x));
}

/**
 * vec2_cross_product_f32 - Computes the cross product of two t_vec2_f32
 *
 * @param vec1 The first 2D float vector
 * @param vec2 The second 2D float vector
 * @return The cross product as a t_f32
 *
 * @infos: The cross product of two 2D vectors results in a scalar value
 *			that represents if the vectors are clockwise or counter-clockwise.
 */
t_f32	vec2_cross_product_f32(t_vec2_f32 vec1, t_vec2_f32 vec2)
{
	return (vec1.x * vec2.y - vec1.y * vec2.x);
}
