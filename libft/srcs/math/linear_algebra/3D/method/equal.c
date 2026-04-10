/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 22:59:36 by adouieb           #+#    #+#             */
/*   Updated: 2026/03/30 23:09:42 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"

t_bool	vec3_i32_equal(t_vec3_i32 vec1, t_vec3_i32 vec2)
{
	return ((vec1.x == vec2.x) && (vec1.y == vec2.y) && (vec1.z == vec2.z));
}

t_bool	vec3_u32_equal(t_vec3_u32 vec1, t_vec3_u32 vec2)
{
	return ((vec1.x == vec2.x) && (vec1.y == vec2.y) && (vec1.z == vec2.z));
}

t_bool	vec3_f32_equal(t_vec3_f32 vec1, t_vec3_f32 vec2)
{
	return ((vec1.x == vec2.x) && (vec1.y == vec2.y) && (vec1.z == vec2.z));
}
