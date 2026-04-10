/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_math_advanced.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 18:45:00 by adouieb           #+#    #+#             */
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
// VEC2 ARRAY TESTS
// ============================================================================

void test_vec2_arr_constructors(void)
{
	TEST_START("vec2_arr constructors and operations");
	
	// vec2_arr_s - create with size
	t_vec2_arr arr = vec2_arr_s(5);
	TEST_ASSERT(arr.vecs != NULL, "vec2_arr_s allocates memory");
	TEST_ASSERT(arr.size == 5, "vec2_arr_s sets correct size");
	TEST_ASSERT(arr.len == 0, "vec2_arr_s initializes len to 0");
	
	// vec2_arr_add_v - add vectors
	t_vec2 v1;
	v1.vec_i = vec2_i32(10, 20);
	arr = vec2_arr_add_v(&arr, v1);
	TEST_ASSERT(arr.len == 1, "vec2_arr_add_v increments length");
	TEST_ASSERT(arr.vecs[0].vec_i.x == 10 && arr.vecs[0].vec_i.y == 20, 
		"vec2_arr_add_v stores correct values");
	
	// Add more vectors
	t_vec2 v2;
	v2.vec_i = vec2_i32(30, 40);
	arr = vec2_arr_add_v(&arr, v2);
	TEST_ASSERT(arr.len == 2, "second add increments length");
	
	// vec2_arr_v - copy array
	t_vec2_arr arr_copy = vec2_arr_v(arr);
	TEST_ASSERT(arr_copy.len == arr.len, "vec2_arr_v copies length");
	TEST_ASSERT(arr_copy.size == arr.size, "vec2_arr_v copies size");
	TEST_ASSERT(arr_copy.vecs != arr.vecs, "vec2_arr_v creates new allocation");
	
	// free_vec2_arr
	free_vec2_arr(&arr);
	TEST_ASSERT(arr.vecs == NULL, "free_vec2_arr sets vecs to NULL");
	TEST_ASSERT(arr.len == 0 && arr.size == 0, "free_vec2_arr resets fields");
	
	free_vec2_arr(&arr_copy);
}

void test_vec2_arr_resize(void)
{
	TEST_START("vec2_arr automatic resizing");
	
	// Create small array
	t_vec2_arr arr = vec2_arr_s(2);
	
	// Add vectors beyond initial capacity
	t_vec2 v;
	v.vec_i = vec2_i32(1, 1);
	arr = vec2_arr_add_v(&arr, v);
	v.vec_i = vec2_i32(2, 2);
	arr = vec2_arr_add_v(&arr, v);
	v.vec_i = vec2_i32(3, 3);
	arr = vec2_arr_add_v(&arr, v);
	
	TEST_ASSERT(arr.len == 3, "array grew beyond initial capacity");
	TEST_ASSERT(arr.size >= 3, "size increased");
	TEST_ASSERT(arr.vecs[0].vec_i.x == 1 && arr.vecs[1].vec_i.x == 2 && 
		arr.vecs[2].vec_i.x == 3, "elements preserved after resize");
	
	free_vec2_arr(&arr);
}

// ============================================================================
// VEC3 ARRAY TESTS
// ============================================================================

void test_vec3_arr_constructors(void)
{
	TEST_START("vec3_arr constructors and operations");
	
	// vec3_arr_s - create with size
	t_vec3_arr arr = vec3_arr_s(5);
	TEST_ASSERT(arr.vecs != NULL, "vec3_arr_s allocates memory");
	TEST_ASSERT(arr.size == 5, "vec3_arr_s sets correct size");
	TEST_ASSERT(arr.len == 0, "vec3_arr_s initializes len to 0");
	
	// vec3_arr_add_v - add vectors
	t_vec3 v1;
	v1.vec_i = vec3_i32(10, 20, 30);
	arr = vec3_arr_add_v(&arr, v1);
	TEST_ASSERT(arr.len == 1, "vec3_arr_add_v increments length");
	TEST_ASSERT(arr.vecs[0].vec_i.x == 10 && arr.vecs[0].vec_i.y == 20 && 
		arr.vecs[0].vec_i.z == 30, "vec3_arr_add_v stores correct values");
	
	// vec3_arr_set_v - set at index
	t_vec3 v2;
	v2.vec_i = vec3_i32(100, 200, 300);
	arr = vec3_arr_set_v(&arr, v2, 0);
	TEST_ASSERT(arr.vecs[0].vec_i.x == 100 && arr.vecs[0].vec_i.y == 200 && 
		arr.vecs[0].vec_i.z == 300, "vec3_arr_set_v updates correctly");
	
	// vec3_arr_v - copy array
	t_vec3_arr arr_copy = vec3_arr_v(arr);
	TEST_ASSERT(arr_copy.len == arr.len, "vec3_arr_v copies length");
	TEST_ASSERT(arr_copy.size == arr.size, "vec3_arr_v copies size");
	
	// free_vec3_arr
	free_vec3_arr(&arr);
	TEST_ASSERT(arr.vecs == NULL, "free_vec3_arr sets vecs to NULL");
	
	free_vec3_arr(&arr_copy);
}

void test_vec3_arr_add_arr(void)
{
	TEST_START("vec3_arr_add_arr - concatenate arrays");
	
	// Create two arrays
	t_vec3_arr arr1 = vec3_arr_s(5);
	t_vec3_arr arr2 = vec3_arr_s(3);
	
	// Add vectors to arr1
	t_vec3 v;
	v.vec_i = vec3_i32(1, 2, 3);
	arr1 = vec3_arr_add_v(&arr1, v);
	v.vec_i = vec3_i32(4, 5, 6);
	arr1 = vec3_arr_add_v(&arr1, v);
	
	// Add vectors to arr2
	v.vec_i = vec3_i32(7, 8, 9);
	arr2 = vec3_arr_add_v(&arr2, v);
	v.vec_i = vec3_i32(10, 11, 12);
	arr2 = vec3_arr_add_v(&arr2, v);
	
	// Concatenate
	arr1 = vec3_arr_add_arr(&arr1, &arr2);
	
	TEST_ASSERT(arr1.len == 4, "vec3_arr_add_arr combines lengths");
	TEST_ASSERT(arr1.vecs[0].vec_i.x == 1, "first element preserved");
	TEST_ASSERT(arr1.vecs[2].vec_i.x == 7, "arr2 elements appended");
	TEST_ASSERT(arr1.vecs[3].vec_i.x == 10, "last element correct");
	
	free_vec3_arr(&arr1);
	free_vec3_arr(&arr2);
}

// ============================================================================
// VEC2 ARRAY MAP TESTS
// ============================================================================

static t_vec2 double_vec2(t_u32 index, t_vec2 vec, void *extra)
{
	(void)index;
	(void)extra;
	vec.vec_f.x *= 2.0f;
	vec.vec_f.y *= 2.0f;
	return vec;
}

void test_vec2_arr_map(void)
{
	TEST_START("vec2_arr_map - transform array elements");
	
	// Create array with vectors
	t_vec2_arr arr = vec2_arr_s(3);
	t_vec2 v;
	v.vec_f = vec2_f32(1.0f, 2.0f);
	arr = vec2_arr_add_v(&arr, v);
	v.vec_f = vec2_f32(3.0f, 4.0f);
	arr = vec2_arr_add_v(&arr, v);
	
	// Save original length before map (which frees arr)
	size_t original_len = arr.len;
	
	// Apply map function
	t_vec2_arr result = vec2_arr_map(&arr, double_vec2, NULL);
	
	TEST_ASSERT(result.len == original_len, "map preserves length");
	TEST_ASSERT(result.vecs[0].vec_f.x == 2.0f && result.vecs[0].vec_f.y == 4.0f, 
		"map transforms first element");
	TEST_ASSERT(result.vecs[1].vec_f.x == 6.0f && result.vecs[1].vec_f.y == 8.0f, 
		"map transforms second element");
	
	free_vec2_arr(&result);
}

// ============================================================================
// VEC3 ARRAY MAP TESTS
// ============================================================================

static t_vec3 scale_vec3(t_u32 index, t_vec3 vec, void *extra)
{
	(void)index;
	t_f32 *scale = (t_f32 *)extra;
	vec.vec_f.x *= *scale;
	vec.vec_f.y *= *scale;
	vec.vec_f.z *= *scale;
	return vec;
}

static t_vec2 vec3_to_vec2(t_u32 index, t_vec3 vec, void *extra)
{
	(void)index;
	(void)extra;
	t_vec2 result;
	result.vec_f = vec2_f32(vec.vec_f.x, vec.vec_f.y);
	return result;
}

void test_vec3_arr_map(void)
{
	TEST_START("vec3 array map functions");
	
	// Test vec3_3_arr_map (vec3 -> vec3)
	t_vec3_arr arr1 = vec3_arr_s(2);
	t_vec3 v;
	v.vec_f = vec3_f32(1.0f, 2.0f, 3.0f);
	arr1 = vec3_arr_add_v(&arr1, v);
	v.vec_f = vec3_f32(4.0f, 5.0f, 6.0f);
	arr1 = vec3_arr_add_v(&arr1, v);
	
	t_f32 scale = 2.0f;
	t_vec3_arr result3 = vec3_3_arr_map(&arr1, scale_vec3, &scale);
	TEST_ASSERT(result3.vecs[0].vec_f.x == 2.0f && result3.vecs[0].vec_f.y == 4.0f && 
		result3.vecs[0].vec_f.z == 6.0f, "vec3_3_arr_map transforms correctly");
	
	// Test vec3_2_arr_map (vec3 -> vec2) - need new array since arr1 was freed
	t_vec3_arr arr2 = vec3_arr_s(2);
	v.vec_f = vec3_f32(1.0f, 2.0f, 3.0f);
	arr2 = vec3_arr_add_v(&arr2, v);
	v.vec_f = vec3_f32(4.0f, 5.0f, 6.0f);
	arr2 = vec3_arr_add_v(&arr2, v);
	
	t_vec2_arr result2 = vec3_2_arr_map(&arr2, vec3_to_vec2, NULL);
	TEST_ASSERT(result2.len == 2, "vec3_2_arr_map preserves length");
	TEST_ASSERT(result2.vecs[0].vec_f.x == 1.0f && result2.vecs[0].vec_f.y == 2.0f, 
		"vec3_2_arr_map projects to 2D");
	
	free_vec3_arr(&result3);
	free_vec2_arr(&result2);
}

// ============================================================================
// VEC3 ARRAY FILTER TESTS
// ============================================================================

static t_bool filter_positive_z(t_u32 index, t_vec3 vec, void *extra)
{
	(void)index;
	(void)extra;
	return vec.vec_f.z > 0.0f;
}

void test_vec3_arr_filter(void)
{
	TEST_START("vec3_3_arr_filter - filter array elements");
	
	// Create array with mixed z values
	t_vec3_arr arr = vec3_arr_s(4);
	t_vec3 v;
	v.vec_f = vec3_f32(1.0f, 1.0f, 5.0f);
	arr = vec3_arr_add_v(&arr, v);
	v.vec_f = vec3_f32(2.0f, 2.0f, -2.0f);
	arr = vec3_arr_add_v(&arr, v);
	v.vec_f = vec3_f32(3.0f, 3.0f, 3.0f);
	arr = vec3_arr_add_v(&arr, v);
	v.vec_f = vec3_f32(4.0f, 4.0f, -1.0f);
	arr = vec3_arr_add_v(&arr, v);
	
	// Filter
	t_vec3_arr filtered = vec3_3_arr_filter(&arr, filter_positive_z, NULL);
	
	TEST_ASSERT(filtered.len == 2, "filter keeps only matching elements");
	TEST_ASSERT(filtered.vecs[0].vec_f.z == 5.0f, "first filtered element correct");
	TEST_ASSERT(filtered.vecs[1].vec_f.z == 3.0f, "second filtered element correct");
	
	free_vec3_arr(&arr);
	free_vec3_arr(&filtered);
}

// ============================================================================
// QUATERNION CONSTRUCTOR TESTS
// ============================================================================

void test_quaternion_constructors(void)
{
	TEST_START("quaternion constructors");
	
	// quaternion - create from axis and angle
	t_vec3_f32 axis = vec3_f32(0.0f, 0.0f, 1.0f);
	t_quaternion q = quaternion(90.0f, axis);
	TEST_ASSERT(q.w != 0.0f, "quaternion creates valid rotation");
	
	// quaternion_q - copy constructor
	t_quaternion q_copy = quaternion_q(q);
	TEST_ASSERT(q_copy.x == q.x && q_copy.y == q.y && 
		q_copy.z == q.z && q_copy.w == q.w, "quaternion_q copies correctly");
}

// ============================================================================
// QUATERNION OPERATION TESTS
// ============================================================================

void test_quaternion_operations(void)
{
	TEST_START("quaternion operations");
	
	// Create a simple quaternion
	t_vec3_f32 axis = vec3_f32(0.0f, 0.0f, 1.0f);
	t_quaternion q = quaternion(45.0f, axis);
	
	// Test inverse
	t_quaternion q_inv = quaternion_inverse(q);
	t_quaternion identity = quaternion_multiply(q, q_inv);
	t_f32 w_magnitude = fabsf(identity.w);
	TEST_ASSERT(w_magnitude >= 0.99f && w_magnitude <= 1.01f, 
		"q * q_inverse ≈ identity (w ≈ 1)");
	
	// Test multiplication
	t_quaternion q1 = quaternion(30.0f, vec3_f32(0.0f, 0.0f, 1.0f));
	t_quaternion q2 = quaternion(60.0f, vec3_f32(0.0f, 0.0f, 1.0f));
	t_quaternion q_combined = quaternion_multiply(q1, q2);
	TEST_ASSERT(q_combined.w != 0.0f, "quaternion multiplication produces valid result");
	
	// Test conjugation (vector rotation)
	t_vec3_f32 vec = vec3_f32(1.0f, 0.0f, 0.0f);
	t_quaternion rot_90 = quaternion(90.0f, vec3_f32(0.0f, 0.0f, 1.0f));
	t_vec3_f32 rotated = quaternion_conjugation(rot_90, vec);
	
	// After 90° rotation around Z, (1,0,0) should become approximately (0,1,0)
	TEST_ASSERT(fabsf(rotated.x) <= 0.1f, "rotation x component near 0");
	TEST_ASSERT(rotated.y >= 0.9f && rotated.y <= 1.1f, "rotation y component near 1");
	TEST_ASSERT(fabsf(rotated.z) <= 0.1f, "rotation z component near 0");
}

// ============================================================================
// MAIN TEST RUNNER
// ============================================================================

void run_math_advanced_tests(void)
{
	test_vec2_arr_constructors();
	test_vec2_arr_resize();
	test_vec3_arr_constructors();
	test_vec3_arr_add_arr();
	test_vec2_arr_map();
	test_vec3_arr_map();
	test_vec3_arr_filter();
	test_quaternion_constructors();
	test_quaternion_operations();
}
