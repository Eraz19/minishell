/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 19:29:00 by adouieb           #+#    #+#             */
/*   Updated: 2026/03/17 19:34:03 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft_math.h"

t_quaternion	quaternion_q(t_quaternion quaternion)
{
	return (vec4_f32_v(quaternion));
}

t_quaternion	quaternion(t_f32 rotation, t_vec3_f32 axis)
{
	t_f32		half_angle;
	t_f32		sin_half;
	t_vec3_f32	norm_axis;

	norm_axis = vec3_normalize_f32(axis);
	half_angle = (rotation * 3.14159265359f) / 360.0f;
	sin_half = sinf(half_angle);
	return (vec4_f32(
			norm_axis.x * sin_half,
			norm_axis.y * sin_half,
			norm_axis.z * sin_half,
			cosf(half_angle)));
}
