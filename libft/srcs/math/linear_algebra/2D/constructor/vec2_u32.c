/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_u32.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 11:38:44 by adouieb           #+#    #+#             */
/*   Updated: 2026/02/28 11:42:07 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"
#include "libft_types.h"

/**
 * vec2_u32_v - Duplicates a 2D vector of unsigned integers structure
 *
 * @param vec The vector to duplicate
 * @return The newly created t_vec2_u32 structure
 */
t_vec2_u32	vec2_u32_v(t_vec2_u32 vec)
{
	return ((t_vec2_u32){.x = vec.x, .y = vec.y});
}

/**
 * vec2_u32 - Creates a 2D vector of unsigned integers structure
 *
 * @param x The x component of the vector
 * @param y The y component of the vector
 * @return The newly created t_vec2_u32 structure
 */
t_vec2_u32	vec2_u32(t_u32 x, t_u32 y)
{
	return ((t_vec2_u32){.x = x, .y = y});
}
