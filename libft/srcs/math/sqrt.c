/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sqrt.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 18:45:51 by adouieb           #+#    #+#             */
/*   Updated: 2026/03/17 19:18:47 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_types.h"

/**
 * sqrt_f - Computes the square root of a float using the Babylonian method
 *
 * @param nbr The float to compute the square root of
 * @return The square root of nbr
 */
t_f32	sqrt_f(t_f32 value)
{
	t_f32	res;
	t_f32	prev;
	t_i32	iter;

	if (value < 0)
		return (0);
	else if (value == 0 || value == 1)
		return (value);
	res = value / 2;
	if (res < 1.0f)
		res = 1.0f;
	iter = 0;
	while (iter++ < 50)
	{
		prev = res;
		res = (res + value / res) / 2;
		if (prev - res < 0.00001f && prev - res > -0.00001f)
			break ;
	}
	return (res);
}

/**
 * sqrt_u - Computes the square root of an integer using the Babylonian method
 *
 * @param nbr The integer to compute the square root of
 * @return The square root of nbr
 */
t_f32	sqrt_u(t_u32 value)
{
	t_f32	res;

	if (value == 0 || value == 1)
		return ((t_f32)value);
	res = (t_f32)value / 2;
	while (res * res > (t_f32)value)
		res = (res + (t_f32)value / res) / 2;
	return (res);
}
