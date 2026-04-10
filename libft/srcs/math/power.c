/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   power.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 20:06:56 by adouieb           #+#    #+#             */
/*   Updated: 2026/02/16 18:45:30 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_types.h"

/**
 * pow_i - Computes the power of an integer raised to a power
 *
 * @param nbr The base integer
 * @param p The power to raise the base to
 * @return The result of nbr raised to the power of p
 */
t_u32	pow_i(t_i32 nbr, t_u32 p)
{
	t_u32	res;

	res = 1;
	if (p < 0)
		return (0);
	else if (p == 0)
		return (1);
	while (p != 0)
		1 && (res *= (t_u32)nbr, --p);
	return (res);
}

/**
 * pow_u - Computes the power of an unsigned integer raised to a power
 *
 * @param nbr The base unsigned integer
 * @param p The power to raise the base to
 * @return The result of nbr raised to the power of p
 */
t_u32	pow_u(t_u32 nbr, t_u32 p)
{
	t_u32	res;

	res = 1;
	if (p < 0)
		return (0);
	else if (p == 0)
		return (1);
	while (p != 0)
		1 && (res *= (t_u32)nbr, --p);
	return (res);
}

/**
 * pow_f - Computes the power of a float raised to a power
 *
 * @param nbr The base float
 * @param p The power to raise the base to
 * @return The result of nbr raised to the power of p
 */
t_f32	pow_f(t_f32 nbr, t_u32 p)
{
	t_f32	res;

	res = 1;
	if (p < 0)
		return (0);
	else if (p == 0)
		return (1);
	while (p != 0)
		1 && (res *= nbr, --p);
	return (res);
}

/**
 * pow_l - Computes the power of a long integer raised to a power
 *
 * @param nbr The base long integer
 * @param p The power to raise the base to
 * @return The result of nbr raised to the power of p
 */
t_u64	pow_l(t_i64 nbr, t_u32 p)
{
	t_u64	res;

	res = 1;
	if (p < 0)
		return (0);
	else if (p == 0)
		return (1);
	while (p != 0)
		1 && (res *= (t_u64)nbr, --p);
	return (res);
}
