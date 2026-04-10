/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceil.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 19:26:53 by adouieb           #+#    #+#             */
/*   Updated: 2026/03/17 19:20:31 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"

/**
 * ceil_float - Ceils a floating-point number to the nearest integer greater
 * 				than or equal to the value.
 *
 * @param value The floating-point number to ceil.
 * @return The ceiled integer value.
 */
t_i32	ceil_float(t_f32 value)
{
	t_i32	int_value;

	int_value = (t_i32)value;
	if (value > 0.0f && (t_f32)int_value != value)
		return (int_value + 1);
	return (int_value);
}
