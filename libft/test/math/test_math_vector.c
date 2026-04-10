/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_math_vector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 18:30:00 by adouieb           #+#    #+#             */
/*   Updated: 2026/03/17 19:18:47 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_test.h"
#include "libft.h"
#include <math.h>

// Override TEST_ASSERT and TEST_SUMMARY to use math-specific counters
#undef TEST_ASSERT
#define TEST_ASSERT MATH_TEST_ASSERT
#undef TEST_SUMMARY
#define TEST_SUMMARY MATH_TEST_SUMMARY

// Test counters (external from test_math_comprehensive.c)
extern int g_math_tests_run;
extern int g_math_tests_passed;
extern int g_math_tests_failed;

// ============================================================================
// VEC2 CONSTRUCTOR TESTS
// ============================================================================

void test_vec2_constructors(void)
{
	TEST_START("vec2 constructors - vec2_i32, vec2_u32, vec2_f32");
	
	// vec2_i32
	t_vec2_i32 v2i = vec2_i32(10, 20);
	TEST_ASSERT(v2i.x == 10 && v2i.y == 20, "vec2_i32(10, 20) correct");
	
	t_vec2_i32 v2i_neg = vec2_i32(-5, -10);
	TEST_ASSERT(v2i_neg.x == -5 && v2i_neg.y == -10, "vec2_i32 handles negatives");
	
	// vec2_u32
	t_vec2_u32 v2u = vec2_u32(15U, 25U);
	TEST_ASSERT(v2u.x == 15U && v2u.y == 25U, "vec2_u32(15, 25) correct");
	
	// vec2_f32
	t_vec2_f32 v2f = vec2_f32(1.5f, 2.5f);
	TEST_ASSERT(v2f.x == 1.5f && v2f.y == 2.5f, "vec2_f32(1.5, 2.5) correct");
	
	// Copy constructors
	t_vec2_i32 v2i_copy = vec2_i32_v(v2i);
	TEST_ASSERT(v2i_copy.x == 10 && v2i_copy.y == 20, "vec2_i32_v copies correctly");
	
	t_vec2_u32 v2u_copy = vec2_u32_v(v2u);
	TEST_ASSERT(v2u_copy.x == 15U && v2u_copy.y == 25U, "vec2_u32_v copies correctly");
	
	t_vec2_f32 v2f_copy = vec2_f32_v(v2f);
	TEST_ASSERT(v2f_copy.x == 1.5f && v2f_copy.y == 2.5f, "vec2_f32_v copies correctly");
}

// ============================================================================
// VEC3 CONSTRUCTOR TESTS
// ============================================================================

void test_vec3_constructors(void)
{
	TEST_START("vec3 constructors - vec3_i32, vec3_u32, vec3_f32");
	
	// vec3_i32
	t_vec3_i32 v3i = vec3_i32(10, 20, 30);
	TEST_ASSERT(v3i.x == 10 && v3i.y == 20 && v3i.z == 30, 
		"vec3_i32(10, 20, 30) correct");
	
	// vec3_u32
	t_vec3_u32 v3u = vec3_u32(15U, 25U, 35U);
	TEST_ASSERT(v3u.x == 15U && v3u.y == 25U && v3u.z == 35U, 
		"vec3_u32(15, 25, 35) correct");
	
	// vec3_f32
	t_vec3_f32 v3f = vec3_f32(1.5f, 2.5f, 3.5f);
	TEST_ASSERT(v3f.x == 1.5f && v3f.y == 2.5f && v3f.z == 3.5f, 
		"vec3_f32(1.5, 2.5, 3.5) correct");
	
	// Copy constructors
	t_vec3_i32 v3i_copy = vec3_i32_v(v3i);
	TEST_ASSERT(v3i_copy.x == 10 && v3i_copy.y == 20 && v3i_copy.z == 30, 
		"vec3_i32_v copies correctly");
	
	t_vec3_u32 v3u_copy = vec3_u32_v(v3u);
	TEST_ASSERT(v3u_copy.x == 15U && v3u_copy.y == 25U && v3u_copy.z == 35U, 
		"vec3_u32_v copies correctly");
	
	t_vec3_f32 v3f_copy = vec3_f32_v(v3f);
	TEST_ASSERT(v3f_copy.x == 1.5f && v3f_copy.y == 2.5f && v3f_copy.z == 3.5f, 
		"vec3_f32_v copies correctly");
}

// ============================================================================
// VEC4 CONSTRUCTOR TESTS
// ============================================================================

void test_vec4_constructors(void)
{
	TEST_START("vec4 constructors - vec4_i32, vec4_u32, vec4_f32");
	
	// vec4_i32
	t_vec4_i32 v4i = vec4_i32(10, 20, 30, 40);
	TEST_ASSERT(v4i.x == 10 && v4i.y == 20 && v4i.z == 30 && v4i.w == 40, 
		"vec4_i32(10, 20, 30, 40) correct");
	
	// vec4_u32
	t_vec4_u32 v4u = vec4_u32(15U, 25U, 35U, 45U);
	TEST_ASSERT(v4u.x == 15U && v4u.y == 25U && v4u.z == 35U && v4u.w == 45U, 
		"vec4_u32(15, 25, 35, 45) correct");
	
	// vec4_f32
	t_vec4_f32 v4f = vec4_f32(1.5f, 2.5f, 3.5f, 4.5f);
	TEST_ASSERT(v4f.x == 1.5f && v4f.y == 2.5f && v4f.z == 3.5f && v4f.w == 4.5f, 
		"vec4_f32(1.5, 2.5, 3.5, 4.5) correct");
	
	// Copy constructors
	t_vec4_i32 v4i_copy = vec4_i32_v(v4i);
	TEST_ASSERT(v4i_copy.x == 10 && v4i_copy.y == 20 && 
		v4i_copy.z == 30 && v4i_copy.w == 40, "vec4_i32_v copies correctly");
	
	t_vec4_u32 v4u_copy = vec4_u32_v(v4u);
	TEST_ASSERT(v4u_copy.x == 15U && v4u_copy.y == 25U && 
		v4u_copy.z == 35U && v4u_copy.w == 45U, "vec4_u32_v copies correctly");
	
	t_vec4_f32 v4f_copy = vec4_f32_v(v4f);
	TEST_ASSERT(v4f_copy.x == 1.5f && v4f_copy.y == 2.5f && 
		v4f_copy.z == 3.5f && v4f_copy.w == 4.5f, "vec4_f32_v copies correctly");
}

// ============================================================================
// VEC2 ADDITION TESTS
// ============================================================================

void test_vec2_addition(void)
{
	TEST_START("vec2 addition - vec2_add_i32, vec2_add_u32, vec2_add_f32");
	
	// vec2_add_i32
	t_vec2_i32 v1 = vec2_i32(10, 20);
	t_vec2_i32 v2 = vec2_i32(5, 15);
	t_vec2_i32 sum_i = vec2_add_i32(v1, v2);
	TEST_ASSERT(sum_i.x == 15 && sum_i.y == 35, "vec2_add_i32(10,20 + 5,15) = (15,35)");
	
	// vec2_add_u32
	t_vec2_u32 v1u = vec2_u32(10U, 20U);
	t_vec2_u32 v2u = vec2_u32(5U, 15U);
	t_vec2_u32 sum_u = vec2_add_u32(v1u, v2u);
	TEST_ASSERT(sum_u.x == 15U && sum_u.y == 35U, "vec2_add_u32 correct");
	
	// vec2_add_f32
	t_vec2_f32 v1f = vec2_f32(1.5f, 2.5f);
	t_vec2_f32 v2f = vec2_f32(0.5f, 1.5f);
	t_vec2_f32 sum_f = vec2_add_f32(v1f, v2f);
	TEST_ASSERT(sum_f.x == 2.0f && sum_f.y == 4.0f, "vec2_add_f32 correct");
}

// ============================================================================
// VEC3 ADDITION TESTS
// ============================================================================

void test_vec3_addition(void)
{
	TEST_START("vec3 addition - vec3_add_i32, vec3_add_u32, vec3_add_f32");
	
	// vec3_add_i32
	t_vec3_i32 v1 = vec3_i32(10, 20, 30);
	t_vec3_i32 v2 = vec3_i32(5, 15, 25);
	t_vec3_i32 sum_i = vec3_add_i32(v1, v2);
	TEST_ASSERT(sum_i.x == 15 && sum_i.y == 35 && sum_i.z == 55, 
		"vec3_add_i32 correct");
	
	// vec3_add_u32
	t_vec3_u32 v1u = vec3_u32(10U, 20U, 30U);
	t_vec3_u32 v2u = vec3_u32(5U, 15U, 25U);
	t_vec3_u32 sum_u = vec3_add_u32(v1u, v2u);
	TEST_ASSERT(sum_u.x == 15U && sum_u.y == 35U && sum_u.z == 55U, 
		"vec3_add_u32 correct");
	
	// vec3_add_f32
	t_vec3_f32 v1f = vec3_f32(1.5f, 2.5f, 3.5f);
	t_vec3_f32 v2f = vec3_f32(0.5f, 1.5f, 2.5f);
	t_vec3_f32 sum_f = vec3_add_f32(v1f, v2f);
	TEST_ASSERT(sum_f.x == 2.0f && sum_f.y == 4.0f && sum_f.z == 6.0f, 
		"vec3_add_f32 correct");
}

// ============================================================================
// VEC2 SUBTRACTION TESTS
// ============================================================================

void test_vec2_subtraction(void)
{
	TEST_START("vec2 subtraction - vec2_sub_i32, vec2_sub_u32, vec2_sub_f32");
	
	// vec2_sub_i32
	t_vec2_i32 v1 = vec2_i32(10, 20);
	t_vec2_i32 v2 = vec2_i32(5, 15);
	t_vec2_i32 diff_i = vec2_sub_i32(v1, v2);
	TEST_ASSERT(diff_i.x == 5 && diff_i.y == 5, "vec2_sub_i32 correct");
	
	// vec2_sub_u32
	t_vec2_u32 v1u = vec2_u32(20U, 30U);
	t_vec2_u32 v2u = vec2_u32(5U, 15U);
	t_vec2_i32 diff_u = vec2_sub_u32(v1u, v2u);
	TEST_ASSERT(diff_u.x == 15 && diff_u.y == 15, "vec2_sub_u32 correct");
	
	// vec2_sub_f32
	t_vec2_f32 v1f = vec2_f32(5.5f, 7.5f);
	t_vec2_f32 v2f = vec2_f32(2.5f, 3.5f);
	t_vec2_f32 diff_f = vec2_sub_f32(v1f, v2f);
	TEST_ASSERT(diff_f.x == 3.0f && diff_f.y == 4.0f, "vec2_sub_f32 correct");
}

// ============================================================================
// VEC3 SUBTRACTION TESTS
// ============================================================================

void test_vec3_subtraction(void)
{
	TEST_START("vec3 subtraction - vec3_sub_i32, vec3_sub_u32, vec3_sub_f32");
	
	// vec3_sub_i32
	t_vec3_i32 v1 = vec3_i32(10, 20, 30);
	t_vec3_i32 v2 = vec3_i32(5, 15, 25);
	t_vec3_i32 diff_i = vec3_sub_i32(v1, v2);
	TEST_ASSERT(diff_i.x == 5 && diff_i.y == 5 && diff_i.z == 5, 
		"vec3_sub_i32 correct");
	
	// vec3_sub_u32
	t_vec3_u32 v1u = vec3_u32(20U, 30U, 40U);
	t_vec3_u32 v2u = vec3_u32(5U, 15U, 25U);
	t_vec3_i32 diff_u = vec3_sub_u32(v1u, v2u);
	TEST_ASSERT(diff_u.x == 15 && diff_u.y == 15 && diff_u.z == 15, 
		"vec3_sub_u32 correct");
	
	// vec3_sub_f32
	t_vec3_f32 v1f = vec3_f32(5.5f, 7.5f, 9.5f);
	t_vec3_f32 v2f = vec3_f32(2.5f, 3.5f, 4.5f);
	t_vec3_f32 diff_f = vec3_sub_f32(v1f, v2f);
	TEST_ASSERT(diff_f.x == 3.0f && diff_f.y == 4.0f && diff_f.z == 5.0f, 
		"vec3_sub_f32 correct");
}

// ============================================================================
// VEC2 MULTIPLICATION TESTS
// ============================================================================

void test_vec2_multiplication(void)
{
	TEST_START("vec2 scalar multiplication");
	
	// vec2_mult_i32
	t_vec2_i32 v1 = vec2_i32(3, 4);
	t_vec2_i32 prod_i = vec2_mult_i32(v1, 2);
	TEST_ASSERT(prod_i.x == 6 && prod_i.y == 8, "vec2_mult_i32(3,4 * 2) = (6,8)");
	
	// vec2_mult_u32
	t_vec2_u32 v1u = vec2_u32(3U, 4U);
	t_vec2_i32 prod_u = vec2_mult_u32(v1u, 2);
	TEST_ASSERT(prod_u.x == 6 && prod_u.y == 8, "vec2_mult_u32 correct");
	
	// vec2_mult_f32
	t_vec2_f32 v1f = vec2_f32(3.0f, 4.0f);
	t_vec2_f32 prod_f = vec2_mult_f32(v1f, 2.5f);
	TEST_ASSERT(prod_f.x == 7.5f && prod_f.y == 10.0f, "vec2_mult_f32 correct");
}

// ============================================================================
// VEC3 MULTIPLICATION TESTS
// ============================================================================

void test_vec3_multiplication(void)
{
	TEST_START("vec3 scalar multiplication");
	
	// vec3_mult_i32
	t_vec3_i32 v1 = vec3_i32(2, 3, 4);
	t_vec3_i32 prod_i = vec3_mult_i32(v1, 3);
	TEST_ASSERT(prod_i.x == 6 && prod_i.y == 9 && prod_i.z == 12, 
		"vec3_mult_i32 correct");
	
	// vec3_mult_u32
	t_vec3_u32 v1u = vec3_u32(2U, 3U, 4U);
	t_vec3_i32 prod_u = vec3_mult_u32(v1u, 3);
	TEST_ASSERT(prod_u.x == 6 && prod_u.y == 9 && prod_u.z == 12, 
		"vec3_mult_u32 correct");
	
	// vec3_mult_f32
	t_vec3_f32 v1f = vec3_f32(2.0f, 3.0f, 4.0f);
	t_vec3_f32 prod_f = vec3_mult_f32(v1f, 2.5f);
	TEST_ASSERT(prod_f.x == 5.0f && prod_f.y == 7.5f && prod_f.z == 10.0f, 
		"vec3_mult_f32 correct");
}

// ============================================================================
// VEC2 NORM TESTS
// ============================================================================

void test_vec2_norm(void)
{
	TEST_START("vec2 norm - magnitude calculation");
	
	// vec2_norm_i32 - 3-4-5 triangle
	t_vec2_i32 v1 = vec2_i32(3, 4);
	t_f32 norm_i = vec2_norm_i32(v1);
	TEST_ASSERT(norm_i >= 4.99f && norm_i <= 5.01f, "vec2_norm_i32(3,4) ≈ 5.0");
	
	// vec2_norm_u32
	t_vec2_u32 v1u = vec2_u32(3U, 4U);
	t_f32 norm_u = vec2_norm_u32(v1u);
	TEST_ASSERT(norm_u >= 4.99f && norm_u <= 5.01f, "vec2_norm_u32 correct");
	
	// vec2_norm_f32
	t_vec2_f32 v1f = vec2_f32(3.0f, 4.0f);
	t_f32 norm_f = vec2_norm_f32(v1f);
	TEST_ASSERT(norm_f >= 4.99f && norm_f <= 5.01f, "vec2_norm_f32 correct");
	
	// Zero vector
	t_vec2_f32 zero = vec2_f32(0.0f, 0.0f);
	TEST_ASSERT(vec2_norm_f32(zero) == 0.0f, "norm of zero vector is 0");
	
	// Unit vectors
	t_vec2_f32 unit_x = vec2_f32(1.0f, 0.0f);
	TEST_ASSERT(vec2_norm_f32(unit_x) >= 0.99f && vec2_norm_f32(unit_x) <= 1.01f, 
		"unit vector norm ≈ 1.0");
}

// ============================================================================
// VEC3 NORM TESTS
// ============================================================================

void test_vec3_norm(void)
{
	TEST_START("vec3 norm - magnitude calculation");
	
	// vec3_norm_i32
	t_vec3_i32 v1 = vec3_i32(2, 3, 6);
	t_f32 norm_i = vec3_norm_i32(v1);
	TEST_ASSERT(norm_i >= 6.99f && norm_i <= 7.01f, "vec3_norm_i32(2,3,6) ≈ 7.0");
	
	// vec3_norm_u32
	t_vec3_u32 v1u = vec3_u32(2U, 3U, 6U);
	t_f32 norm_u = vec3_norm_u32(v1u);
	TEST_ASSERT(norm_u >= 6.99f && norm_u <= 7.01f, "vec3_norm_u32 correct");
	
	// vec3_norm_f32
	t_vec3_f32 v1f = vec3_f32(2.0f, 3.0f, 6.0f);
	t_f32 norm_f = vec3_norm_f32(v1f);
	TEST_ASSERT(norm_f >= 6.99f && norm_f <= 7.01f, "vec3_norm_f32 correct");
	
	// Zero vector
	t_vec3_f32 zero = vec3_f32(0.0f, 0.0f, 0.0f);
	TEST_ASSERT(vec3_norm_f32(zero) == 0.0f, "norm of zero vector is 0");
}

// ============================================================================
// VEC4 NORM TESTS
// ============================================================================

void test_vec4_norm(void)
{
	TEST_START("vec4 norm - magnitude calculation");
	
	// vec4_norm_i32
	t_vec4_i32 v1 = vec4_i32(1, 2, 2, 4);
	t_f32 norm_i = vec4_norm_i32(v1);
	TEST_ASSERT(norm_i >= 4.99f && norm_i <= 5.01f, "vec4_norm_i32 correct");
	
	// vec4_norm_u32
	t_vec4_u32 v1u = vec4_u32(1U, 2U, 2U, 4U);
	t_f32 norm_u = vec4_norm_u32(v1u);
	TEST_ASSERT(norm_u >= 4.99f && norm_u <= 5.01f, "vec4_norm_u32 correct");
	
	// vec4_norm_f32
	t_vec4_f32 v1f = vec4_f32(1.0f, 2.0f, 2.0f, 4.0f);
	t_f32 norm_f = vec4_norm_f32(v1f);
	TEST_ASSERT(norm_f >= 4.99f && norm_f <= 5.01f, "vec4_norm_f32 correct");
}

// ============================================================================
// VEC2 NORMALIZE TESTS
// ============================================================================

void test_vec2_normalize(void)
{
	TEST_START("vec2 normalize - unit vector creation");
	
	// vec2_normalize_i32
	t_vec2_i32 v1 = vec2_i32(3, 4);
	t_vec2_f32 unit_i = vec2_normalize_i32(v1);
	t_f32 norm = vec2_norm_f32(unit_i);
	TEST_ASSERT(norm >= 0.99f && norm <= 1.01f, "vec2_normalize_i32 creates unit vector");
	
	// vec2_normalize_u32
	t_vec2_u32 v1u = vec2_u32(3U, 4U);
	t_vec2_f32 unit_u = vec2_normalize_u32(v1u);
	norm = vec2_norm_f32(unit_u);
	TEST_ASSERT(norm >= 0.99f && norm <= 1.01f, "vec2_normalize_u32 creates unit vector");
	
	// vec2_normalize_f32
	t_vec2_f32 v1f = vec2_f32(3.0f, 4.0f);
	t_vec2_f32 unit_f = vec2_normalize_f32(v1f);
	norm = vec2_norm_f32(unit_f);
	TEST_ASSERT(norm >= 0.99f && norm <= 1.01f, "vec2_normalize_f32 creates unit vector");
}

// ============================================================================
// VEC3 NORMALIZE TESTS
// ============================================================================

void test_vec3_normalize(void)
{
	TEST_START("vec3 normalize - unit vector creation");
	
	// vec3_normalize_i32
	t_vec3_i32 v1 = vec3_i32(2, 3, 6);
	t_vec3_f32 unit_i = vec3_normalize_i32(v1);
	t_f32 norm = vec3_norm_f32(unit_i);
	TEST_ASSERT(norm >= 0.99f && norm <= 1.01f, "vec3_normalize_i32 creates unit vector");
	
	// vec3_normalize_u32
	t_vec3_u32 v1u = vec3_u32(2U, 3U, 6U);
	t_vec3_f32 unit_u = vec3_normalize_u32(v1u);
	norm = vec3_norm_f32(unit_u);
	TEST_ASSERT(norm >= 0.99f && norm <= 1.01f, "vec3_normalize_u32 creates unit vector");
	
	// vec3_normalize_f32
	t_vec3_f32 v1f = vec3_f32(2.0f, 3.0f, 6.0f);
	t_vec3_f32 unit_f = vec3_normalize_f32(v1f);
	norm = vec3_norm_f32(unit_f);
	TEST_ASSERT(norm >= 0.99f && norm <= 1.01f, "vec3_normalize_f32 creates unit vector");
}

// ============================================================================
// VEC4 NORMALIZE TESTS
// ============================================================================

void test_vec4_normalize(void)
{
	TEST_START("vec4 normalize - unit vector creation");
	
	// vec4_normalize_i32
	t_vec4_i32 v1 = vec4_i32(1, 2, 2, 4);
	t_vec4_f32 unit_i = vec4_normalize_i32(v1);
	t_f32 norm = vec4_norm_f32(unit_i);
	TEST_ASSERT(norm >= 0.99f && norm <= 1.01f, "vec4_normalize_i32 creates unit vector");
	
	// vec4_normalize_u32
	t_vec4_u32 v1u = vec4_u32(1U, 2U, 2U, 4U);
	t_vec4_f32 unit_u = vec4_normalize_u32(v1u);
	norm = vec4_norm_f32(unit_u);
	TEST_ASSERT(norm >= 0.99f && norm <= 1.01f, "vec4_normalize_u32 creates unit vector");
	
	// vec4_normalize_f32
	t_vec4_f32 v1f = vec4_f32(1.0f, 2.0f, 2.0f, 4.0f);
	t_vec4_f32 unit_f = vec4_normalize_f32(v1f);
	norm = vec4_norm_f32(unit_f);
	TEST_ASSERT(norm >= 0.99f && norm <= 1.01f, "vec4_normalize_f32 creates unit vector");
}

// ============================================================================
// VEC2 DOT PRODUCT TESTS
// ============================================================================

void test_vec2_dot_product(void)
{
	TEST_START("vec2 dot product");
	
	// vec2_dot_product_i32
	t_vec2_i32 v1 = vec2_i32(2, 3);
	t_vec2_i32 v2 = vec2_i32(4, 5);
	t_i32 dot_i = vec2_dot_product_i32(v1, v2);
	TEST_ASSERT(dot_i == 23, "vec2_dot_product_i32(2,3 · 4,5) = 23");
	
	// vec2_dot_product_u32
	t_vec2_u32 v1u = vec2_u32(2U, 3U);
	t_vec2_u32 v2u = vec2_u32(4U, 5U);
	t_u32 dot_u = vec2_dot_product_u32(v1u, v2u);
	TEST_ASSERT(dot_u == 23U, "vec2_dot_product_u32 correct");
	
	// vec2_dot_product_f32
	t_vec2_f32 v1f = vec2_f32(2.0f, 3.0f);
	t_vec2_f32 v2f = vec2_f32(4.0f, 5.0f);
	t_f32 dot_f = vec2_dot_product_f32(v1f, v2f);
	TEST_ASSERT(dot_f == 23.0f, "vec2_dot_product_f32 correct");
	
	// Perpendicular vectors (dot = 0)
	t_vec2_f32 perp1 = vec2_f32(1.0f, 0.0f);
	t_vec2_f32 perp2 = vec2_f32(0.0f, 1.0f);
	TEST_ASSERT(vec2_dot_product_f32(perp1, perp2) == 0.0f, 
		"perpendicular vectors have dot product 0");
}

// ============================================================================
// VEC3 DOT PRODUCT TESTS
// ============================================================================

void test_vec3_dot_product(void)
{
	TEST_START("vec3 dot product");
	
	// vec3_dot_product_i32
	t_vec3_i32 v1 = vec3_i32(1, 2, 3);
	t_vec3_i32 v2 = vec3_i32(4, 5, 6);
	t_i32 dot_i = vec3_dot_product_i32(v1, v2);
	TEST_ASSERT(dot_i == 32, "vec3_dot_product_i32(1,2,3 · 4,5,6) = 32");
	
	// vec3_dot_product_u32
	t_vec3_u32 v1u = vec3_u32(1U, 2U, 3U);
	t_vec3_u32 v2u = vec3_u32(4U, 5U, 6U);
	t_u32 dot_u = vec3_dot_product_u32(v1u, v2u);
	TEST_ASSERT(dot_u == 32U, "vec3_dot_product_u32 correct");
	
	// vec3_dot_product_f32
	t_vec3_f32 v1f = vec3_f32(1.0f, 2.0f, 3.0f);
	t_vec3_f32 v2f = vec3_f32(4.0f, 5.0f, 6.0f);
	t_f32 dot_f = vec3_dot_product_f32(v1f, v2f);
	TEST_ASSERT(dot_f == 32.0f, "vec3_dot_product_f32 correct");
}

// ============================================================================
// VEC2 CROSS PRODUCT TESTS
// ============================================================================

void test_vec2_cross_product(void)
{
	TEST_START("vec2 cross product (scalar)");
	
	// vec2_cross_product_i32
	t_vec2_i32 v1 = vec2_i32(3, 2);
	t_vec2_i32 v2 = vec2_i32(1, 4);
	t_i32 cross_i = vec2_cross_product_i32(v1, v2);
	TEST_ASSERT(cross_i == 10, "vec2_cross_product_i32(3,2 × 1,4) = 10");
	
	// vec2_cross_product_u32
	t_vec2_u32 v1u = vec2_u32(3U, 2U);
	t_vec2_u32 v2u = vec2_u32(1U, 4U);
	t_i32 cross_u = vec2_cross_product_u32(v1u, v2u);
	TEST_ASSERT(cross_u == 10, "vec2_cross_product_u32 correct");
	
	// vec2_cross_product_f32
	t_vec2_f32 v1f = vec2_f32(3.0f, 2.0f);
	t_vec2_f32 v2f = vec2_f32(1.0f, 4.0f);
	t_f32 cross_f = vec2_cross_product_f32(v1f, v2f);
	TEST_ASSERT(cross_f == 10.0f, "vec2_cross_product_f32 correct");
}

// ============================================================================
// VEC3 CROSS PRODUCT TESTS
// ============================================================================

void test_vec3_cross_product(void)
{
	TEST_START("vec3 cross product");
	
	// vec3_cross_product_i32 - standard basis vectors
	t_vec3_i32 i = vec3_i32(1, 0, 0);
	t_vec3_i32 j = vec3_i32(0, 1, 0);
	t_vec3_i32 cross_i = vec3_cross_product_i32(i, j);
	TEST_ASSERT(cross_i.x == 0 && cross_i.y == 0 && cross_i.z == 1, 
		"i × j = k");
	
	// vec3_cross_product_u32
	t_vec3_u32 iu = vec3_u32(1U, 0U, 0U);
	t_vec3_u32 ju = vec3_u32(0U, 1U, 0U);
	t_vec3_i32 cross_u = vec3_cross_product_u32(iu, ju);
	TEST_ASSERT(cross_u.x == 0 && cross_u.y == 0 && cross_u.z == 1, 
		"vec3_cross_product_u32 correct");
	
	// vec3_cross_product_f32
	t_vec3_f32 if32 = vec3_f32(1.0f, 0.0f, 0.0f);
	t_vec3_f32 jf32 = vec3_f32(0.0f, 1.0f, 0.0f);
	t_vec3_f32 cross_f = vec3_cross_product_f32(if32, jf32);
	TEST_ASSERT(cross_f.x >= -0.01f && cross_f.x <= 0.01f && 
		cross_f.y >= -0.01f && cross_f.y <= 0.01f && 
		cross_f.z >= 0.99f && cross_f.z <= 1.01f, 
		"vec3_cross_product_f32 correct");
	
	// General case
	t_vec3_i32 v1 = vec3_i32(2, 3, 4);
	t_vec3_i32 v2 = vec3_i32(5, 6, 7);
	t_vec3_i32 cross = vec3_cross_product_i32(v1, v2);
	// Expected: (-3, 6, -3)
	TEST_ASSERT(cross.x == -3 && cross.y == 6 && cross.z == -3, 
		"vec3_cross_product general case correct");
}

// ============================================================================
// VEC2 SWAP TESTS
// ============================================================================

void test_vec2_swap(void)
{
	TEST_START("vec2 swap");
	
	// vec2_swap_i32
	t_vec2_i32 v1 = vec2_i32(10, 20);
	t_vec2_i32 v2 = vec2_i32(30, 40);
	vec2_swap_i32(&v1, &v2);
	TEST_ASSERT(v1.x == 30 && v1.y == 40 && v2.x == 10 && v2.y == 20, 
		"vec2_swap_i32 swaps correctly");
	
	// vec2_swap_u32
	t_vec2_u32 v1u = vec2_u32(10U, 20U);
	t_vec2_u32 v2u = vec2_u32(30U, 40U);
	vec2_swap_u32(&v1u, &v2u);
	TEST_ASSERT(v1u.x == 30U && v1u.y == 40U && v2u.x == 10U && v2u.y == 20U, 
		"vec2_swap_u32 swaps correctly");
	
	// vec2_swap_f32
	t_vec2_f32 v1f = vec2_f32(1.5f, 2.5f);
	t_vec2_f32 v2f = vec2_f32(3.5f, 4.5f);
	vec2_swap_f32(&v1f, &v2f);
	TEST_ASSERT(v1f.x == 3.5f && v1f.y == 4.5f && v2f.x == 1.5f && v2f.y == 2.5f, 
		"vec2_swap_f32 swaps correctly");
}

// ============================================================================
// MAIN TEST RUNNER
// ============================================================================

void run_math_vector_tests(void)
{
	test_vec2_constructors();
	test_vec3_constructors();
	test_vec4_constructors();
	test_vec2_addition();
	test_vec3_addition();
	test_vec2_subtraction();
	test_vec3_subtraction();
	test_vec2_multiplication();
	test_vec3_multiplication();
	test_vec2_norm();
	test_vec3_norm();
	test_vec4_norm();
	test_vec2_normalize();
	test_vec3_normalize();
	test_vec4_normalize();
	test_vec2_dot_product();
	test_vec3_dot_product();
	test_vec2_cross_product();
	test_vec3_cross_product();
	test_vec2_swap();
}
