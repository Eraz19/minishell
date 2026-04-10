/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 09:48:02 by adouieb           #+#    #+#             */
/*   Updated: 2026/03/17 19:39:42 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"
#include "libft_types.h"

/**
 * vec3_norm_i32 - Computes the norm of a t_vec3D of integers
 *
 * @param vec The 3D vector with integer components
 * @return The norm of the vector as a float
 */
t_f32	vec3_norm_i32(t_vec3_i32 vec)
{
	return (sqrt_u(pow_i(vec.x, 2) + pow_i(vec.y, 2) + pow_i(vec.z, 2)));
}

/**
 * vec3_norm_u32 - Computes the norm of a t_vec3D of unsigned integers
 *
 * @param vec The 3D vector with unsigned integer components
 * @return The norm of the vector as a float
 */
t_f32	vec3_norm_u32(t_vec3_u32 vec)
{
	return (sqrt_u(pow_u(vec.x, 2) + pow_u(vec.y, 2) + pow_u(vec.z, 2)));
}

/**
 * vec3_norm_f32 - Computes the norm of a t_vec3D of floats
 *
 * @param vec The 3D vector with float components
 * @return The norm of the vector as a float
 */
t_f32	vec3_norm_f32(t_vec3_f32 vec)
{
	return (sqrt_f(pow_f(vec.x, 2) + pow_f(vec.y, 2) + pow_f(vec.z, 2)));
}
