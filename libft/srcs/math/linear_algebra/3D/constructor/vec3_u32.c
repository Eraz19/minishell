/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_u32.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 16:13:59 by adouieb           #+#    #+#             */
/*   Updated: 2026/02/28 11:56:14 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"
#include "libft_types.h"

/**
 * vec3_u32_v - Duplicates a 3D vector of unsigned integers structure
 *
 * @param vec The t_vec3_u32 structure to duplicate
 * @return The newly created t_vec3_u32 structure
 */
t_vec3_u32	vec3_u32_v(t_vec3_u32 vec)
{
	return ((t_vec3_u32){.x = vec.x, .y = vec.y, .z = vec.z});
}

/**
 * vec3_u32 - Creates a 3D vector of unsigned integers structure
 *
 * @param x The x component of the vector
 * @param y The y component of the vector
 * @param z The z component of the vector
 * @return The newly created t_vec3_u32 structure
 */
t_vec3_u32	vec3_u32(t_u32 x, t_u32 y, t_u32 z)
{
	return ((t_vec3_u32){.x = x, .y = y, .z = z});
}
