/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4_i32.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 16:13:59 by adouieb           #+#    #+#             */
/*   Updated: 2026/02/28 12:03:56 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"
#include "libft_types.h"

/**
 * vec4_i32_v - Duplicates a 4D vector of integers structure
 *
 * @param vec The t_vec4_i32 structure to duplicate
 * @return The newly created t_vec4_i32 structure
 */
t_vec4_i32	vec4_i32_v(t_vec4_i32 vec)
{
	return ((t_vec4_i32){.x = vec.x, .y = vec.y, .z = vec.z, .w = vec.w});
}

/**
 * vec4_i32 - Creates a 4D vector of integers structure
 *
 * @param x The x component of the vector
 * @param y The y component of the vector
 * @param z The z component of the vector
 * @param w The w component of the vector
 * @return The newly created t_vec4_i32 structure
 */
t_vec4_i32	vec4_i32(t_i32 x, t_i32 y, t_i32 z, t_i32 w)
{
	return ((t_vec4_i32){.x = x, .y = y, .z = z, .w = w});
}
