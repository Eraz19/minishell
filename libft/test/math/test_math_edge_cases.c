/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_math_edge_cases.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 19:00:00 by adouieb           #+#    #+#             */
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
// VEC2_ARR MALLOC FAILURE TESTS
// ============================================================================

void test_vec2_arr_malloc_failures(void)
{
	TEST_START("vec2_arr malloc failure handling");
	
	// Test vec2_arr_s malloc failure
	malloc_fail_enable();
	malloc_fail_after(0);
	t_vec2_arr arr = vec2_arr_s(5);
	TEST_ASSERT(arr.vecs == NULL && arr.size == 0 && arr.len == 0, 
		"vec2_arr_s handles malloc failure");
	malloc_fail_disable();
	
	// Test vec2_arr_add_v malloc failure (during resize)
	arr = vec2_arr_s(1);
	TEST_ASSERT(arr.vecs != NULL, "vec2_arr_s succeeds");
	
	t_vec2 v;
	v.vec_i = vec2_i32(1, 1);
	arr = vec2_arr_add_v(&arr, v);
	TEST_ASSERT(arr.len == 1, "first add succeeds");
	
	// Force malloc failure on resize
	malloc_fail_enable();
	malloc_fail_after(0);
	v.vec_i = vec2_i32(2, 2);
	t_vec2_arr result = vec2_arr_add_v(&arr, v);
	TEST_ASSERT(result.len == 1, "add handles resize malloc failure");
	malloc_fail_disable();
	
	free_vec2_arr(&arr);
	
	// Test vec2_arr_v malloc failure
	arr = vec2_arr_s(2);
	v.vec_i = vec2_i32(10, 20);
	arr = vec2_arr_add_v(&arr, v);
	
	malloc_fail_enable();
	malloc_fail_after(0);
	t_vec2_arr copy = vec2_arr_v(arr);
	TEST_ASSERT(copy.vecs == NULL && copy.size == 0 && copy.len == 0, 
		"vec2_arr_v handles malloc failure");
	malloc_fail_disable();
	
	free_vec2_arr(&arr);
	
	// Test vec2_arr_map malloc failure
	arr = vec2_arr_s(2);
	v.vec_i = vec2_i32(1, 1);
	arr = vec2_arr_add_v(&arr, v);
	
	malloc_fail_enable();
	malloc_fail_after(0);
	t_vec2_arr mapped = vec2_arr_map(&arr, NULL, NULL);
	TEST_ASSERT(mapped.vecs == NULL, "vec2_arr_map handles malloc failure");
	malloc_fail_disable();
	
	free_vec2_arr(&arr);
}

// ============================================================================
// VEC3_ARR MALLOC FAILURE TESTS
// ============================================================================

void test_vec3_arr_malloc_failures(void)
{
	TEST_START("vec3_arr malloc failure handling");
	
	// Test vec3_arr_s malloc failure
	malloc_fail_enable();
	malloc_fail_after(0);
	t_vec3_arr arr = vec3_arr_s(5);
	TEST_ASSERT(arr.vecs == NULL && arr.size == 0 && arr.len == 0, 
		"vec3_arr_s handles malloc failure");
	malloc_fail_disable();
	
	// Test vec3_arr_add_v malloc failure
	arr = vec3_arr_s(1);
	TEST_ASSERT(arr.vecs != NULL, "vec3_arr_s succeeds");
	
	t_vec3 v;
	v.vec_i = vec3_i32(1, 1, 1);
	arr = vec3_arr_add_v(&arr, v);
	TEST_ASSERT(arr.len == 1, "first add succeeds");
	
	// Force malloc failure on resize
	malloc_fail_enable();
	malloc_fail_after(0);
	v.vec_i = vec3_i32(2, 2, 2);
	t_vec3_arr result = vec3_arr_add_v(&arr, v);
	TEST_ASSERT(result.len == 1, "add handles resize malloc failure");
	malloc_fail_disable();
	
	free_vec3_arr(&arr);
	
	// Test vec3_arr_v malloc failure
	arr = vec3_arr_s(2);
	v.vec_i = vec3_i32(10, 20, 30);
	arr = vec3_arr_add_v(&arr, v);
	
	malloc_fail_enable();
	malloc_fail_after(0);
	t_vec3_arr copy = vec3_arr_v(arr);
	TEST_ASSERT(copy.vecs == NULL && copy.size == 0 && copy.len == 0, 
		"vec3_arr_v handles malloc failure");
	malloc_fail_disable();
	
	free_vec3_arr(&arr);
	
	// Test vec3_arr_add_arr malloc failure
	t_vec3_arr arr1 = vec3_arr_s(1);
	t_vec3_arr arr2 = vec3_arr_s(1);
	v.vec_i = vec3_i32(1, 1, 1);
	arr1 = vec3_arr_add_v(&arr1, v);
	v.vec_i = vec3_i32(2, 2, 2);
	arr2 = vec3_arr_add_v(&arr2, v);
	
	malloc_fail_enable();
	malloc_fail_after(0);
	t_vec3_arr combined = vec3_arr_add_arr(&arr1, &arr2);
	TEST_ASSERT(combined.len == 1, "vec3_arr_add_arr handles malloc failure");
	malloc_fail_disable();
	
	free_vec3_arr(&arr1);
	free_vec3_arr(&arr2);
	
	// Test vec3_3_arr_map malloc failure
	arr = vec3_arr_s(2);
	v.vec_i = vec3_i32(1, 1, 1);
	arr = vec3_arr_add_v(&arr, v);
	
	malloc_fail_enable();
	malloc_fail_after(0);
	t_vec3_arr mapped = vec3_3_arr_map(&arr, NULL, NULL);
	TEST_ASSERT(mapped.vecs == NULL, "vec3_3_arr_map handles malloc failure");
	malloc_fail_disable();
	
	free_vec3_arr(&arr);
	
	// Test vec3_2_arr_map malloc failure
	arr = vec3_arr_s(2);
	v.vec_i = vec3_i32(1, 1, 1);
	arr = vec3_arr_add_v(&arr, v);
	
	malloc_fail_enable();
	malloc_fail_after(0);
	t_vec2_arr mapped2 = vec3_2_arr_map(&arr, NULL, NULL);
	TEST_ASSERT(mapped2.vecs == NULL, "vec3_2_arr_map handles malloc failure");
	malloc_fail_disable();
	
	free_vec3_arr(&arr);
	
	// Test vec3_3_arr_filter malloc failure
	arr = vec3_arr_s(2);
	v.vec_i = vec3_i32(1, 1, 1);
	arr = vec3_arr_add_v(&arr, v);
	
	malloc_fail_enable();
	malloc_fail_after(0);
	t_vec3_arr filtered = vec3_3_arr_filter(&arr, NULL, NULL);
	TEST_ASSERT(filtered.vecs == NULL, "vec3_3_arr_filter handles malloc failure");
	malloc_fail_disable();
	
	free_vec3_arr(&arr);
}

// ============================================================================
// EDGE CASE TESTS - DIVISION BY ZERO, OVERFLOW, ETC
// ============================================================================

void test_sqrt_edge_cases(void)
{
	TEST_START("sqrt edge cases");
	
	// Zero input
	TEST_ASSERT(sqrt_f(0.0f) == 0.0f, "sqrt(0) = 0");
	TEST_ASSERT(sqrt_u(0U) == 0.0f, "sqrt(0U) = 0");
	
	// Very small values
	t_f32 small = sqrt_f(0.0001f);
	TEST_ASSERT(small >= 0.009f && small <= 0.011f, "sqrt(0.0001) ≈ 0.01");
	
	// Very large values
	t_f32 large = sqrt_u(1000000U);
	TEST_ASSERT(large >= 999.0f && large <= 1001.0f, "sqrt(1000000) ≈ 1000");
}

void test_normalize_zero_vector(void)
{
	TEST_START("normalize zero vector edge case");
	
	// vec2 zero vector normalization
	t_vec2_i32 v2_zero = vec2_i32(0, 0);
	t_vec2_f32 norm2 = vec2_normalize_i32(v2_zero);
	// Should return zero vector or handle gracefully
	TEST_ASSERT(norm2.x == 0.0f || isnan(norm2.x), "normalize(0,0) handles zero");
	
	// vec3 zero vector normalization
	t_vec3_i32 v3_zero = vec3_i32(0, 0, 0);
	t_vec3_f32 norm3 = vec3_normalize_i32(v3_zero);
	TEST_ASSERT(norm3.x == 0.0f || isnan(norm3.x), "normalize(0,0,0) handles zero");
	
	// vec4 zero vector normalization
	t_vec4_i32 v4_zero = vec4_i32(0, 0, 0, 0);
	t_vec4_f32 norm4 = vec4_normalize_i32(v4_zero);
	TEST_ASSERT(norm4.x == 0.0f || isnan(norm4.x), "normalize(0,0,0,0) handles zero");
}

void test_power_edge_cases(void)
{
	TEST_START("power function edge cases");
	
	// Large exponents
	TEST_ASSERT(pow_u(2U, 20) == 1048576U, "2^20 correct");
	TEST_ASSERT(pow_u(10U, 6) == 1000000U, "10^6 correct");
	
	// Base of 1
	TEST_ASSERT(pow_i(1, 100) == 1, "1^100 = 1");
	TEST_ASSERT(pow_u(1U, 100) == 1U, "1^100 = 1");
	TEST_ASSERT(pow_f(1.0f, 100) == 1.0f, "1.0^100 = 1.0");
	
	// Negative base with even/odd powers
	TEST_ASSERT(pow_i(-1, 2) == 1, "(-1)^2 = 1");
	TEST_ASSERT(pow_i(-1, 100) == 1, "(-1)^100 = 1");
}

void test_rounding_edge_cases(void)
{
	TEST_START("rounding edge cases");
	
	// Exact halfway cases
	TEST_ASSERT(round_float(2.5f) == 3, "round(2.5) = 3");
	TEST_ASSERT(round_float(-2.5f) == -3, "round(-2.5) = -3");
	
	// Very large numbers
	TEST_ASSERT(round_float(1000000.4f) == 1000000, "round large number");
	TEST_ASSERT(floor_float(1000000.9f) == 1000000, "floor large number");
	TEST_ASSERT(ceil_float(1000000.1f) == 1000001, "ceil large number");
	
	// Very small fractions
	TEST_ASSERT(round_float(0.0001f) == 0, "round(0.0001) = 0");
	TEST_ASSERT(round_float(-0.0001f) == 0, "round(-0.0001) = 0");
}

void test_vector_overflow_edge_cases(void)
{
	TEST_START("vector operation overflow handling");
	
	// vec2 with max values
	t_vec2_i32 v_max = vec2_i32(I32_MAX, I32_MAX);
	t_f32 norm = vec2_norm_i32(v_max);
	TEST_ASSERT(norm > 0.0f && !isinf(norm), "norm handles large values");
	
	// vec3 with max values
	t_vec3_i32 v3_max = vec3_i32(I32_MAX, I32_MAX, I32_MAX);
	t_f32 norm3 = vec3_norm_i32(v3_max);
	TEST_ASSERT(norm3 > 0.0f && !isinf(norm3), "vec3 norm handles large values");
	
	// Addition near overflow
	t_vec2_i32 v1 = vec2_i32(I32_MAX - 10, 100);
	t_vec2_i32 v2 = vec2_i32(5, 200);
	vec2_add_i32(v1, v2);
	// May overflow, but should not crash
	TEST_ASSERT(TRUE, "addition doesn't crash on overflow");
}

void test_arr_empty_operations(void)
{
	TEST_START("array operations on empty arrays");
	
	// Empty vec2_arr operations
	t_vec2_arr empty2 = vec2_arr_s(0);
	TEST_ASSERT(empty2.vecs == NULL && empty2.len == 0, "empty vec2_arr created");
	
	// Map on empty array
	t_vec2_arr mapped = vec2_arr_map(&empty2, NULL, NULL);
	TEST_ASSERT(mapped.len == 0, "map on empty array returns empty");
	
	free_vec2_arr(&empty2);
	free_vec2_arr(&mapped);
	
	// Empty vec3_arr operations
	t_vec3_arr empty3 = vec3_arr_s(0);
	TEST_ASSERT(empty3.vecs == NULL && empty3.len == 0, "empty vec3_arr created");
	
	// Filter on empty array
	t_vec3_arr filtered = vec3_3_arr_filter(&empty3, NULL, NULL);
	TEST_ASSERT(filtered.len == 0, "filter on empty array returns empty");
	
	free_vec3_arr(&empty3);
	free_vec3_arr(&filtered);
}

void test_arr_set_out_of_bounds(void)
{
	TEST_START("vec3_arr_set_v out of bounds handling");
	
	t_vec3_arr arr = vec3_arr_s(3);
	t_vec3 v;
	v.vec_i = vec3_i32(1, 1, 1);
	arr = vec3_arr_add_v(&arr, v);
	
	// Try to set beyond current length
	v.vec_i = vec3_i32(99, 99, 99);
	t_vec3_arr result = vec3_arr_set_v(&arr, v, 100);
	
	// Should either handle gracefully or not modify
	TEST_ASSERT(result.len == 1, "set out of bounds handled gracefully");
	
	free_vec3_arr(&arr);
}

void test_null_pointer_safety(void)
{
	TEST_START("NULL pointer safety checks");
	
	// free functions with NULL
	free_vec2_arr(NULL);
	TEST_ASSERT(TRUE, "free_vec2_arr(NULL) doesn't crash");
	
	free_vec3_arr(NULL);
	TEST_ASSERT(TRUE, "free_vec3_arr(NULL) doesn't crash");
	
	// Operations on arrays with NULL vecs pointer
	t_vec2_arr null_arr2;
	null_arr2.vecs = NULL;
	null_arr2.len = 0;
	null_arr2.size = 0;
	
	t_vec2 v2;
	v2.vec_i = vec2_i32(1, 1);
	t_vec2_arr result2 = vec2_arr_add_v(&null_arr2, v2);
	TEST_ASSERT(result2.len >= 0, "add_v on NULL array handled");
	
	free_vec2_arr(&result2);
	
	t_vec3_arr null_arr3;
	null_arr3.vecs = NULL;
	null_arr3.len = 0;
	null_arr3.size = 0;
	
	t_vec3 v3;
	v3.vec_i = vec3_i32(1, 1, 1);
	t_vec3_arr result3 = vec3_arr_add_v(&null_arr3, v3);
	TEST_ASSERT(result3.len >= 0, "add_v on NULL array handled");
	
	free_vec3_arr(&result3);
}

// ============================================================================
// MAIN TEST RUNNER
// ============================================================================

void run_math_edge_case_tests(void)
{
	test_vec2_arr_malloc_failures();
	test_vec3_arr_malloc_failures();
	test_sqrt_edge_cases();
	test_normalize_zero_vector();
	test_power_edge_cases();
	test_rounding_edge_cases();
	test_vector_overflow_edge_cases();
	test_arr_empty_operations();
	test_arr_set_out_of_bounds();
	test_null_pointer_safety();
}
