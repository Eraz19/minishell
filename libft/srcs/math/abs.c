/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:46:42 by adouieb           #+#    #+#             */
/*   Updated: 2026/03/09 21:59:33 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_types.h"

/**
 * abs_i - Computes the absolute value of a signed integer
 *
 * @param c The signed integer value
 * @return The absolute value as an unsigned integer
 */
t_u32	abs_i(t_i32 c)
{
	if (c == I32_MIN)
		return ((t_u32)I32_MAX + 1);
	if (c < 0)
		return ((t_u32)(-c));
	else
		return ((t_u32)c);
}

/**
 * abs_l - Computes the absolute value of a signed long integer
 *
 * @param c The signed long integer value
 * @return The absolute value as an unsigned long integer
 */
t_u64	abs_l(t_i64 c)
{
	if (c == I64_MIN)
		return ((t_u64)I64_MAX + 1);
	if (c < 0)
		return ((t_u64)(-c));
	else
		return ((t_u64)c);
}

/**
 * abs_f - Computes the absolute value of a floating-point number
 *
 * @param c The floating-point value
 * @return The absolute value as a floating-point number
 */
t_f32	abs_f(t_f32 c)
{
	if (c < 0)
		return (-c);
	else
		return (c);
}
