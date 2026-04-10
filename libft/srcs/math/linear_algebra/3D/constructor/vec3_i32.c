/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_i32.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 16:13:59 by adouieb           #+#    #+#             */
/*   Updated: 2026/02/28 11:54:58 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"
#include "libft_types.h"

/**
 * vec3_i32_v - Duplicates a 3D vector of integers structure
 *
 * @param vec The t_vec3_i32 structure to duplicate
 * @return The newly created t_vec3_i32 structure
 */
t_vec3_i32	vec3_i32_v(t_vec3_i32 vec)
{
	return ((t_vec3_i32){.x = vec.x, .y = vec.y, .z = vec.z});
}

/**
 * vec3_i32 - Creates a 3D vector of integers structure
 *
 * @param x The x component of the vector
 * @param y The y component of the vector
 * @param z The z component of the vector
 * @return The newly created t_vec3_i32 structure
 */
t_vec3_i32	vec3_i32(t_i32 x, t_i32 y, t_i32 z)
{
	return ((t_vec3_i32){.x = x, .y = y, .z = z});
}
