/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 09:52:38 by adouieb           #+#    #+#             */
/*   Updated: 2026/03/17 19:31:41 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"
#include "libft_types.h"

/**
 * quaternion_multiply - Multiplies two quaternions together
 *
 * @param quat1 The first quaternion
 * @param quat2 The second quaternion
 * @return The product of the two quaternions
 *
 * @info: Quaternion multiplication is not commutative, meaning that the order
 * 			of the quaternions matters. It represents the composition of two
 * 			rotations in 3D space.
 */
t_quaternion	quaternion_multiply(t_quaternion quat1, t_quaternion quat2)
{
	return (
		vec4_f32(
			quat1.w * quat2.x
			+ quat1.x * quat2.w
			+ quat1.y * quat2.z
			- quat1.z * quat2.y,
			quat1.w * quat2.y
			- quat1.x * quat2.z
			+ quat1.y * quat2.w
			+ quat1.z * quat2.x,
			quat1.w * quat2.z
			+ quat1.x * quat2.y
			- quat1.y * quat2.x
			+ quat1.z * quat2.w,
			quat1.w * quat2.w
			- quat1.x * quat2.x
			- quat1.y * quat2.y
			- quat1.z * quat2.z)
	);
}

/**
 * quaternion_conjugation - Applies the conjugation of a quaternion to a vector
 *
 * @param quat The quaternion to conjugate with
 * @param vec The vector to be transformed
 * @return The transformed vector
 *
 * @info: Quaternion conjugation is used to rotate a vector in 3D space by a
 * 			quaternion. It is defined as q * v * q^-1.
 */
t_vec3_f32	quaternion_conjugation(t_quaternion quat, t_vec3_f32 vec)
{
	t_vec3_f32	quat_vec;
	t_vec3_f32	quat_vec_cross;

	quat_vec = vec3_f32(quat.x, quat.y, quat.z);
	quat_vec_cross = vec3_cross_product_f32(quat_vec, vec);
	return (
		vec3_add_f32(
			vec3_add_f32(vec, vec3_mult_f32(quat_vec_cross, 2 * quat.w)),
			vec3_mult_f32(vec3_cross_product_f32(quat_vec, quat_vec_cross), 2))
	);
}

/**
 * quaternion_inverse - Computes the inverse of a quaternion
 *
 * @param quat The quaternion to invert
 * @return The inverse of the quaternion
 *
 * @info: The inverse of a quaternion represents the opposite rotation in the
 *			inverse coordinate system (rather than having a rotation in the
 *			x, y, z axes it'll be in the -x, -y, -z axes).
 */
t_quaternion	quaternion_inverse(t_quaternion quat)
{
	return (vec4_f32(-quat.x, -quat.y, -quat.z, quat.w));
}
