/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 16:56:39 by adouieb           #+#    #+#             */
/*   Updated: 2026/02/24 17:05:47 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"

/**
 * vec2_swap_i32 - Swap two t_vec2_i32 vectors
 *
 * @param vec1 The first 2D integer vector
 * @param vec2 The second 2D integer vector
 * @return void
 */
void	vec2_swap_i32(t_vec2_i32 *vec1, t_vec2_i32 *vec2)
{
	t_vec2_i32	temp;

	temp = *vec1;
	*vec1 = *vec2;
	*vec2 = temp;
}

/**
 * vec2_swap_u32 - Swap two t_vec2_u32 vectors
 *
 * @param vec1 The first 2D unsigned integer vector
 * @param vec2 The second 2D unsigned integer vector
 * @return void
 */
void	vec2_swap_u32(t_vec2_u32 *vec1, t_vec2_u32 *vec2)
{
	t_vec2_u32	temp;

	temp = *vec1;
	*vec1 = *vec2;
	*vec2 = temp;
}

/**
 * vec2_swap_f32 - Swap two t_vec2_f32 vectors
 *
 * @param vec1 The first 2D floating-point vector
 * @param vec2 The second 2D floating-point vector
 * @return void
 */
void	vec2_swap_f32(t_vec2_f32 *vec1, t_vec2_f32 *vec2)
{
	t_vec2_f32	temp;

	temp = *vec1;
	*vec1 = *vec2;
	*vec2 = temp;
}
