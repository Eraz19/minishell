/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_f32.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 16:13:59 by adouieb           #+#    #+#             */
/*   Updated: 2026/02/28 11:53:40 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"
#include "libft_types.h"

/**
 * vec3_f32_v - Duplicates a 3D vector of floating-point numbers structure
 *
 * @param vec The t_vec3_f32 structure to duplicate
 * @return The newly created t_vec3_f32 structure
 */
t_vec3_f32	vec3_f32_v(t_vec3_f32 vec)
{
	return ((t_vec3_f32){.x = vec.x, .y = vec.y, .z = vec.z});
}

/**
 * vec3_f32 - Creates a 3D vector of floating-point numbers structure
 *
 * @param x The x component of the vector
 * @param y The y component of the vector
 * @param z The z component of the vector
 * @return The newly created t_vec3_f32 structure
 */
t_vec3_f32	vec3_f32(t_f32 x, t_f32 y, t_f32 z)
{
	return ((t_vec3_f32){.x = x, .y = y, .z = z});
}
