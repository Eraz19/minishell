/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_f32.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 15:28:47 by adouieb           #+#    #+#             */
/*   Updated: 2026/02/28 11:40:54 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"
#include "libft_types.h"

/**
 * vec2_f32_v - Duplicates a 2D vector of floating-point numbers structure
 *
 * @param vec The vector to duplicate
 * @return The newly created t_vec2_f32 structure
 */
t_vec2_f32	vec2_f32_v(t_vec2_f32 vec)
{
	return ((t_vec2_f32){.x = vec.x, .y = vec.y});
}

/**
 * vec2_f32 - Creates a 2D vector of floating-point numbers structure
 *
 * @param x The x component of the vector
 * @param y The y component of the vector
 * @return The newly created t_vec2_f32 structure
 */
t_vec2_f32	vec2_f32(t_f32 x, t_f32 y)
{
	return ((t_vec2_f32){.x = x, .y = y});
}
