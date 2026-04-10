/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiply.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 10:02:56 by adouieb           #+#    #+#             */
/*   Updated: 2026/02/19 17:49:33 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"
#include "libft_types.h"

/**
 * vec2_mult_i32 - Multiplies a t_vec2_i32 vector by a scalar
 *
 * @param vec The 2D integer vector
 * @param scalar The scalar value to multiply with
 * @return The resulting vector of the multiplication
 *
 * @infos: The multiplication of a vector by a scalar applies a scaling to the
 *			vector by the scalar.
 */
t_vec2_i32	vec2_mult_i32(t_vec2_i32 vec, t_i32 scalar)
{
	return (vec2_i32(vec.x * scalar, vec.y * scalar));
}

/**
 * vec2_mult_u32 - Multiplies a t_vec2_u32 vector by a scalar
 *
 * @param vec The 2D unsigned integer vector
 * @param scalar The scalar value to multiply with
 * @return The resulting vector of the multiplication
 *
 * @infos: The multiplication of a vector by a scalar applies a scaling to the
 *			vector by the scalar.
 */
t_vec2_i32	vec2_mult_u32(t_vec2_u32 vec, t_i32 scalar)
{
	return (vec2_i32((t_i32)vec.x * scalar, (t_i32)vec.y * scalar));
}

/**
 * vec2_mult_f32 - Multiplies a t_vec2_f32 vector by a scalar
 *
 * @param vec The 2D float vector
 * @param scalar The scalar value to multiply with
 * @return The resulting vector of the multiplication
 *
 * @infos: The multiplication of a vector by a scalar applies a scaling to the
 *			vector by the scalar.
 */
t_vec2_f32	vec2_mult_f32(t_vec2_f32 vec, t_f32 scalar)
{
	return (vec2_f32(vec.x * scalar, vec.y * scalar));
}
