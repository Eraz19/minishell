/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 18:40:16 by adouieb           #+#    #+#             */
/*   Updated: 2026/02/19 09:45:49 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"
#include "libft_types.h"

/**
 * vec2_norm_i32 - Computes the norm of a t_vec2D of integers
 *
 * @param vec The 2D vector with integer components
 * @return The norm of the vector as a float
 */
t_f32	vec2_norm_i32(t_vec2_i32 vec)
{
	return (sqrt_u(pow_i(vec.x, 2) + pow_i(vec.y, 2)));
}

/**
 * vec2_norm_u32 - Computes the norm of a t_vec2D of unsigned integers
 *
 * @param vec The 2D vector with unsigned integer components
 * @return The norm of the vector as a float
 */
t_f32	vec2_norm_u32(t_vec2_u32 vec)
{
	return (sqrt_u(pow_u(vec.x, 2) + pow_u(vec.y, 2)));
}

/**
 * vec2_norm_f32 - Computes the norm of a t_vec2D of floats
 *
 * @param vec The 2D vector with float components
 * @return The norm of the vector as a float
 */
t_f32	vec2_norm_f32(t_vec2_f32 vec)
{
	return (sqrt_f(pow_f(vec.x, 2) + pow_f(vec.y, 2)));
}
