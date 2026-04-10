/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 15:16:05 by adouieb           #+#    #+#             */
/*   Updated: 2026/02/19 17:54:30 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"
#include "libft_types.h"

/**
 * vec2_add_i32 - Adds two t_vec2_i32 vectors
 *
 * @param vec1 The first 2D integer vector
 * @param vec2 The second 2D integer vector
 * @return The resulting vector of the addition
 *
 * @infos: The addition of two vectors applies a translation to the first vector
 *			by the second vector.
 */
t_vec2_i32	vec2_add_i32(t_vec2_i32 vec1, t_vec2_i32 vec2)
{
	return (vec2_i32(vec1.x + vec2.x, vec1.y + vec2.y));
}

/**
 * vec2_add_u32 - Adds two t_vec2_u32 vectors
 *
 * @param vec1 The first 2D unsigned integer vector
 * @param vec2 The second 2D unsigned integer vector
 * @return The resulting vector of the addition
 *
 * @infos: The addition of two vectors applies a translation to the first vector
 *			by the second vector.
 */
t_vec2_u32	vec2_add_u32(t_vec2_u32 vec1, t_vec2_u32 vec2)
{
	return (vec2_u32(vec1.x + vec2.x, vec1.y + vec2.y));
}

/**
 * vec2_add_f32 - Adds two t_vec2_f32 vectors
 *
 * @param vec1 The first 2D float vector
 * @param vec2 The second 2D float vector
 * @return The resulting vector of the addition
 *
 * @infos: The addition of two vectors applies a translation to the first vector
 *			by the second vector.
 */
t_vec2_f32	vec2_add_f32(t_vec2_f32 vec1, t_vec2_f32 vec2)
{
	return (vec2_f32(vec1.x + vec2.x, vec1.y + vec2.y));
}
