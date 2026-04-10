/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_math.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 19:05:18 by adouieb           #+#    #+#             */
/*   Updated: 2026/03/30 23:06:31 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MATH_H
# define LIBFT_MATH_H

# include "libft_types.h"

typedef struct s_vec2_i32
{
	t_i32	x;
	t_i32	y;
}	t_vec2_i32;
typedef struct s_vec2_u32
{
	t_u32	x;
	t_u32	y;
}	t_vec2_u32;
typedef struct s_vec2_f32
{
	t_f32	x;
	t_f32	y;
}	t_vec2_f32;
typedef union s_vec2
{
	t_vec2_f32	vec_f;
	t_vec2_i32	vec_i;
	t_vec2_u32	vec_u;
}	t_vec2;
typedef struct s_vec2_arr
{
	t_vec2	*vecs;
	size_t	len;
	size_t	size;
}	t_vec2_arr;

typedef struct s_vec3_i32
{
	t_i32	x;
	t_i32	y;
	t_i32	z;
}	t_vec3_i32;
typedef struct s_vec3_u32
{
	t_u32	x;
	t_u32	y;
	t_u32	z;
}	t_vec3_u32;
typedef struct s_vec3_f32
{
	t_f32	x;
	t_f32	y;
	t_f32	z;
}	t_vec3_f32;
typedef union s_vec3
{
	t_vec3_f32	vec_f;
	t_vec3_i32	vec_i;
	t_vec3_u32	vec_u;
}	t_vec3;
typedef struct s_vec3_arr
{
	t_vec3	*vecs;
	size_t	len;
	size_t	size;
}	t_vec3_arr;

typedef struct s_vec4_i32
{
	t_i32	x;
	t_i32	y;
	t_i32	z;
	t_i32	w;
}	t_vec4_i32;
typedef struct s_vec4_u32
{
	t_u32	x;
	t_u32	y;
	t_u32	z;
	t_u32	w;
}	t_vec4_u32;
typedef struct s_vec4_f32
{
	t_f32	x;
	t_f32	y;
	t_f32	z;
	t_f32	w;
}	t_vec4_f32;

typedef t_vec4_f32	t_quaternion;

t_u32			abs_i(t_i32 c);
t_u64			abs_l(t_i64 c);
t_f32			abs_f(t_f32 c);

t_bool			is_prime_u(t_u32 nb);
t_bool			is_prime_l(t_u64 nb);

t_f32			max_f32(t_f32 a, t_f32 b);
t_i32			max_i32(t_i32 a, t_i32 b);
t_u32			max_u32(t_u32 a, t_u32 b);

t_f32			min_f32(t_f32 a, t_f32 b);
t_i32			min_i32(t_i32 a, t_i32 b);
t_u32			min_u32(t_u32 a, t_u32 b);

t_u32			pow_i(t_i32 nbr, t_u32 p);
t_u32			pow_u(t_u32 nbr, t_u32 p);
t_f32			pow_f(t_f32 nbr, t_u32 p);
t_u64			pow_l(t_i64 nbr, t_u32 p);

t_f32			sqrt_f(t_f32 value);
t_f32			sqrt_u(t_u32 value);

t_i32			round_float(t_f32 value);
t_i32			floor_float(t_f32 value);
t_i32			ceil_float(t_f32 value);

t_vec3_arr		vec3_arr_s(size_t size);
t_vec3_arr		vec3_arr_v(t_vec3_arr arr);
t_vec3_i32		vec3_i32_v(t_vec3_i32 vec);
t_vec3_u32		vec3_u32_v(t_vec3_u32 vec);
t_vec3_f32		vec3_f32_v(t_vec3_f32 vec);
t_vec3_i32		vec3_i32(t_i32 x, t_i32 y, t_i32 z);
t_vec3_u32		vec3_u32(t_u32 x, t_u32 y, t_u32 z);
t_vec3_f32		vec3_f32(t_f32 x, t_f32 y, t_f32 z);

t_vec2_arr		vec2_arr_s(size_t size);
t_vec2_arr		vec2_arr_v(t_vec2_arr arr);
t_vec2_i32		vec2_i32(t_i32 x, t_i32 y);
t_vec2_i32		vec2_i32_v(t_vec2_i32 vec);
t_vec2_u32		vec2_u32(t_u32 x, t_u32 y);
t_vec2_u32		vec2_u32_v(t_vec2_u32 vec);
t_vec2_f32		vec2_f32(t_f32 x, t_f32 y);
t_vec2_f32		vec2_f32_v(t_vec2_f32 vec);

t_vec4_i32		vec4_i32_v(t_vec4_i32 vec);
t_vec4_u32		vec4_u32_v(t_vec4_u32 vec);
t_vec4_f32		vec4_f32_v(t_vec4_f32 vec);
t_vec4_i32		vec4_i32(t_i32 x, t_i32 y, t_i32 z, t_i32 w);
t_vec4_u32		vec4_u32(t_u32 x, t_u32 y, t_u32 z, t_u32 w);
t_vec4_f32		vec4_f32(t_f32 x, t_f32 y, t_f32 z, t_f32 w);

t_quaternion	quaternion_q(t_quaternion quaternion);		
t_quaternion	quaternion(t_f32 rotation, t_vec3_f32 axis);

void			free_vec2_arr(t_vec2_arr *vec_arr);
void			free_vec3_arr(t_vec3_arr *vec_arr);

t_vec2_arr		vec2_arr_add_v(t_vec2_arr *arr, t_vec2 vec);
t_vec3_arr		vec3_arr_add_v(t_vec3_arr *arr, t_vec3 vec);
t_vec3_arr		vec3_arr_add_arr(t_vec3_arr *arr, t_vec3_arr *vec);

t_vec3_arr		vec3_arr_set_v(t_vec3_arr *arr, t_vec3 vec, size_t index);

t_vec2_arr		vec2_arr_map(t_vec2_arr *arr,
					t_vec2 (*f)(t_u32, t_vec2, void*), void *extra);
t_vec3_arr		vec3_3_arr_map(t_vec3_arr *arr,
					t_vec3 (*f)(t_u32, t_vec3, void*), void *extra);
t_vec2_arr		vec3_2_arr_map(t_vec3_arr *arr,
					t_vec2 (*f)(t_u32, t_vec3, void*), void *extra);

t_vec3_arr		vec3_3_arr_filter(t_vec3_arr *arr,
					t_bool (*f)(t_u32, t_vec3, void*), void *extra);

t_vec2_i32		vec2_add_i32(t_vec2_i32 vec1, t_vec2_i32 vec2);
t_vec2_u32		vec2_add_u32(t_vec2_u32 vec1, t_vec2_u32 vec2);
t_vec2_f32		vec2_add_f32(t_vec2_f32 vec1, t_vec2_f32 vec2);
t_vec3_i32		vec3_add_i32(t_vec3_i32 vec1, t_vec3_i32 vec2);
t_vec3_u32		vec3_add_u32(t_vec3_u32 vec1, t_vec3_u32 vec2);
t_vec3_f32		vec3_add_f32(t_vec3_f32 vec1, t_vec3_f32 vec2);

t_vec2_i32		vec2_sub_i32(t_vec2_i32 vec1, t_vec2_i32 vec2);
t_vec2_i32		vec2_sub_u32(t_vec2_u32 vec1, t_vec2_u32 vec2);
t_vec2_f32		vec2_sub_f32(t_vec2_f32 vec1, t_vec2_f32 vec2);
t_vec3_i32		vec3_sub_i32(t_vec3_i32 vec1, t_vec3_i32 vec2);
t_vec3_i32		vec3_sub_u32(t_vec3_u32 vec1, t_vec3_u32 vec2);
t_vec3_f32		vec3_sub_f32(t_vec3_f32 vec1, t_vec3_f32 vec2);

t_vec2_i32		vec2_mult_i32(t_vec2_i32 vec, t_i32 scalar);
t_vec2_i32		vec2_mult_u32(t_vec2_u32 vec, t_i32 scalar);
t_vec2_f32		vec2_mult_f32(t_vec2_f32 vec, t_f32 scalar);
t_vec3_i32		vec3_mult_i32(t_vec3_i32 vec, t_i32 scalar);
t_vec3_i32		vec3_mult_u32(t_vec3_u32 vec, t_i32 scalar);
t_vec3_f32		vec3_mult_f32(t_vec3_f32 vec, t_f32 scalar);

t_bool			vec2_i32_equal(t_vec2_i32 vec1, t_vec2_i32 vec2);
t_bool			vec2_u32_equal(t_vec2_u32 vec1, t_vec2_u32 vec2);
t_bool			vec2_f32_equal(t_vec2_f32 vec1, t_vec2_f32 vec2);
t_bool			vec3_i32_equal(t_vec3_i32 vec1, t_vec3_i32 vec2);
t_bool			vec3_u32_equal(t_vec3_u32 vec1, t_vec3_u32 vec2);
t_bool			vec3_f32_equal(t_vec3_f32 vec1, t_vec3_f32 vec2);
t_bool			vec4_i32_equal(t_vec4_i32 vec1, t_vec4_i32 vec2);
t_bool			vec4_u32_equal(t_vec4_u32 vec1, t_vec4_u32 vec2);
t_bool			vec4_f32_equal(t_vec4_f32 vec1, t_vec4_f32 vec2);

t_f32			vec2_norm_i32(t_vec2_i32 vec);
t_f32			vec2_norm_u32(t_vec2_u32 vec);
t_f32			vec2_norm_f32(t_vec2_f32 vec);
t_f32			vec3_norm_i32(t_vec3_i32 vec);
t_f32			vec3_norm_u32(t_vec3_u32 vec);
t_f32			vec3_norm_f32(t_vec3_f32 vec);
t_f32			vec4_norm_i32(t_vec4_i32 vec);
t_f32			vec4_norm_u32(t_vec4_u32 vec);
t_f32			vec4_norm_f32(t_vec4_f32 vec);

t_vec2_f32		vec2_normalize_i32(t_vec2_i32 vec);
t_vec2_f32		vec2_normalize_u32(t_vec2_u32 vec);
t_vec2_f32		vec2_normalize_f32(t_vec2_f32 vec);
t_vec3_f32		vec3_normalize_i32(t_vec3_i32 vec);
t_vec3_f32		vec3_normalize_u32(t_vec3_u32 vec);
t_vec3_f32		vec3_normalize_f32(t_vec3_f32 vec);
t_vec4_f32		vec4_normalize_i32(t_vec4_i32 vec);
t_vec4_f32		vec4_normalize_u32(t_vec4_u32 vec);
t_vec4_f32		vec4_normalize_f32(t_vec4_f32 vec);

t_i32			vec2_dot_product_i32(t_vec2_i32 vec1, t_vec2_i32 vec2);
t_u32			vec2_dot_product_u32(t_vec2_u32 vec1, t_vec2_u32 vec2);
t_f32			vec2_dot_product_f32(t_vec2_f32 vec1, t_vec2_f32 vec2);
t_i32			vec3_dot_product_i32(t_vec3_i32 vec1, t_vec3_i32 vec2);
t_u32			vec3_dot_product_u32(t_vec3_u32 vec1, t_vec3_u32 vec2);
t_f32			vec3_dot_product_f32(t_vec3_f32 vec1, t_vec3_f32 vec2);

void			vec2_swap_i32(t_vec2_i32 *vec1, t_vec2_i32 *vec2);
void			vec2_swap_u32(t_vec2_u32 *vec1, t_vec2_u32 *vec2);
void			vec2_swap_f32(t_vec2_f32 *vec1, t_vec2_f32 *vec2);

t_i32			vec2_cross_product_i32(t_vec2_i32 vec1, t_vec2_i32 vec2);
t_i32			vec2_cross_product_u32(t_vec2_u32 vec1, t_vec2_u32 vec2);
t_f32			vec2_cross_product_f32(t_vec2_f32 vec1, t_vec2_f32 vec2);
t_vec3_i32		vec3_cross_product_i32(t_vec3_i32 vec1, t_vec3_i32 vec2);
t_vec3_i32		vec3_cross_product_u32(t_vec3_u32 vec1, t_vec3_u32 vec2);
t_vec3_f32		vec3_cross_product_f32(t_vec3_f32 vec1, t_vec3_f32 vec2);

t_quaternion	quaternion_inverse(t_quaternion quat);
t_quaternion	quaternion_multiply(t_quaternion quat1, t_quaternion quat2);
t_vec3_f32		quaternion_conjugation(t_quaternion quat, t_vec3_f32 vec);	

#endif
