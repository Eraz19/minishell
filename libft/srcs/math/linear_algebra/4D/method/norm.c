/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 09:53:25 by adouieb           #+#    #+#             */
/*   Updated: 2026/02/19 14:27:10 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"
#include "libft_types.h"

/**
 * vec4_norm_i32 - Computes the norm of a t_vec4D of integers
 *
 * @param vec The 4D vector with integer components
 * @return The norm of the vector as a float
 */
t_f32	vec4_norm_i32(t_vec4_i32 vec)
{
	return (
		sqrt_u(
			pow_i(vec.x, 2)
			+ pow_i(vec.y, 2)
			+ pow_i(vec.z, 2)
			+ pow_i(vec.w, 2))
	);
}

/**
 * vec4_norm_u32 - Computes the norm of a t_vec4D of unsigned integers
 *
 * @param vec The 4D vector with unsigned integer components
 * @return The norm of the vector as a float
 */
t_f32	vec4_norm_u32(t_vec4_u32 vec)
{
	return (
		sqrt_u(
			pow_u(vec.x, 2)
			+ pow_u(vec.y, 2)
			+ pow_u(vec.z, 2)
			+ pow_u(vec.w, 2))
	);
}

/**
 * vec4_norm_f32 - Computes the norm of a t_vec4D of floats
 *
 * @param vec The 4D vector with float components
 * @return The norm of the vector as a float
 */
t_f32	vec4_norm_f32(t_vec4_f32 vec)
{
	return (
		sqrt_f(
			pow_f(vec.x, 2)
			+ pow_f(vec.y, 2)
			+ pow_f(vec.z, 2)
			+ pow_f(vec.w, 2))
	);
}
