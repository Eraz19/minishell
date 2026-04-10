/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_i32.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 11:38:24 by adouieb           #+#    #+#             */
/*   Updated: 2026/03/17 19:37:50 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"
#include "libft_types.h"

/**
 * vec2_i32_v - Duplicates a 2D vector of integers structure
 *
 * @param vec The vector to duplicate
 * @return The newly created t_vec2_i32 structure
 */
t_vec2_i32	vec2_i32_v(t_vec2_i32 vec)
{
	return ((t_vec2_i32){.x = vec.x, .y = vec.y});
}

/**
 * vec2_i32 - Creates a 2D vector of integers structure
 *
 * @param x The x component of the vector
 * @param y The y component of the vector
 * @return The newly created t_vec2_i32 structure
 */
t_vec2_i32	vec2_i32(t_i32 x, t_i32 y)
{
	return ((t_vec2_i32){.x = x, .y = y});
}
