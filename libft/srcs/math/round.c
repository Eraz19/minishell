/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   round.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 23:44:55 by adouieb           #+#    #+#             */
/*   Updated: 2026/03/17 19:21:10 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_types.h"

/**
 * round_float - Rounds a floating-point number to the nearest integer.
 *
 * @param value The floating-point number to round.
 * @return The rounded integer value.
 */
t_i32	round_float(t_f32 value)
{
	if (value >= 0.0f)
		return ((t_i32)(value + 0.5f));
	else
		return ((t_i32)(value - 0.5f));
}
