/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 12:39:17 by adouieb           #+#    #+#             */
/*   Updated: 2026/03/05 12:48:44 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_types.h"

/**
 * max_f32 - Returns the maximum of two floating-point numbers
 *
 * @param a The first floating-point number
 * @param b The second floating-point number
 * @return The maximum of the two numbers
 */
t_f32	max_f32(t_f32 a, t_f32 b)
{
	if (a > b)
		return (a);
	return (b);
}

/**
 * max_i32 - Returns the maximum of two 32-bit integers
 *
 * @param a The first 32-bit integer
 * @param b The second 32-bit integer
 * @return The maximum of the two numbers
 */
t_i32	max_i32(t_i32 a, t_i32 b)
{
	if (a > b)
		return (a);
	return (b);
}

/**
 * max_u32 - Returns the maximum of two 32-bit unsigned integers
 *
 * @param a The first 32-bit unsigned integer
 * @param b The second 32-bit unsigned integer
 * @return The maximum of the two numbers
 */
t_u32	max_u32(t_u32 a, t_u32 b)
{
	if (a > b)
		return (a);
	return (b);
}
