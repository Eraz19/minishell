/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_math_comprehensive.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: GitHub Copilot                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 19:00:00 by Copilot           #+#    #+#             */
/*   Updated: 2026/01/19 19:00:00 by Copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_test.h"
#include "libft.h"

#include <limits.h>

// Override TEST_ASSERT and TEST_SUMMARY to use math-specific counters
#undef TEST_ASSERT
#define TEST_ASSERT MATH_TEST_ASSERT
#undef TEST_SUMMARY
#define TEST_SUMMARY MATH_TEST_SUMMARY

// Test counters (shared across test files)
int g_math_tests_run = 0;
int g_math_tests_passed = 0;
int g_math_tests_failed = 0;

// ============================================================================
// ABSOLUTE VALUE TESTS - abs_i
// ============================================================================

void test_abs_i(void)
{
	TEST_START("abs_i - absolute value for 32-bit integers");
	
	// Positive numbers
	TEST_ASSERT(abs_i(0) == 0, "abs(0) returns 0");
	TEST_ASSERT(abs_i(1) == 1, "abs(1) returns 1");
	TEST_ASSERT(abs_i(42) == 42, "abs(42) returns 42");
	TEST_ASSERT(abs_i(12345) == 12345, "abs(12345) returns 12345");
	TEST_ASSERT(abs_i(I32_MAX) == (t_u32)I32_MAX, "abs(INT_MAX) returns INT_MAX");
	
	// Negative numbers
	TEST_ASSERT(abs_i(-1) == 1, "abs(-1) returns 1");
	TEST_ASSERT(abs_i(-42) == 42, "abs(-42) returns 42");
	TEST_ASSERT(abs_i(-12345) == 12345, "abs(-12345) returns 12345");
	TEST_ASSERT(abs_i(-100) == 100, "abs(-100) returns 100");
	
	// Edge case: INT_MIN
	TEST_ASSERT(abs_i(I32_MIN) == (t_u32)I32_MAX + 1, 
		"abs(INT_MIN) returns INT_MAX + 1 (as unsigned)");
	
	// Values near boundaries
	TEST_ASSERT(abs_i(I32_MAX - 1) == (t_u32)(I32_MAX - 1), 
		"abs(INT_MAX - 1) correct");
	TEST_ASSERT(abs_i(I32_MIN + 1) == (t_u32)I32_MAX, 
		"abs(INT_MIN + 1) returns INT_MAX");
}

// ============================================================================
// ABSOLUTE VALUE TESTS - abs_l
// ============================================================================

void test_abs_l(void)
{
	TEST_START("abs_l - absolute value for 64-bit integers");
	
	// Positive numbers
	TEST_ASSERT(abs_l(0L) == 0UL, "abs(0L) returns 0");
	TEST_ASSERT(abs_l(1L) == 1UL, "abs(1L) returns 1");
	TEST_ASSERT(abs_l(42L) == 42UL, "abs(42L) returns 42");
	TEST_ASSERT(abs_l(123456789L) == 123456789UL, "abs(123456789L) returns 123456789");
	TEST_ASSERT(abs_l(I64_MAX) == (t_u64)I64_MAX, "abs(LONG_MAX) returns LONG_MAX");
	
	// Negative numbers
	TEST_ASSERT(abs_l(-1L) == 1UL, "abs(-1L) returns 1");
	TEST_ASSERT(abs_l(-42L) == 42UL, "abs(-42L) returns 42");
	TEST_ASSERT(abs_l(-123456789L) == 123456789UL, "abs(-123456789L) returns 123456789");
	TEST_ASSERT(abs_l(-1000L) == 1000UL, "abs(-1000L) returns 1000");
	
	// Edge case: LONG_MIN
	TEST_ASSERT(abs_l(I64_MIN) == (t_u64)I64_MAX + 1, 
		"abs(LONG_MIN) returns LONG_MAX + 1 (as unsigned)");
	
	// Values near boundaries
	TEST_ASSERT(abs_l(I64_MAX - 1) == (t_u64)(I64_MAX - 1), 
		"abs(LONG_MAX - 1) correct");
	TEST_ASSERT(abs_l(I64_MIN + 1) == (t_u64)I64_MAX, 
		"abs(LONG_MIN + 1) returns LONG_MAX");
	
	// Large values
	TEST_ASSERT(abs_l(1000000000000L) == 1000000000000UL, 
		"abs(1000000000000L) correct");
	TEST_ASSERT(abs_l(-1000000000000L) == 1000000000000UL, 
		"abs(-1000000000000L) correct");
}

// ============================================================================
// CROSS-SIZE COMPARISON TESTS
// ============================================================================

void test_abs_comparison(void)
{
	TEST_START("abs_i and abs_l - consistency checks");
	
	// Same values should produce same results for both functions
	TEST_ASSERT(abs_i(42) == abs_l(42L), "abs_i(42) == abs_l(42L)");
	TEST_ASSERT(abs_i(-42) == abs_l(-42L), "abs_i(-42) == abs_l(-42L)");
	TEST_ASSERT(abs_i(0) == abs_l(0L), "abs_i(0) == abs_l(0L)");
	TEST_ASSERT(abs_i(I32_MAX) == abs_l((t_i64)I32_MAX), 
		"abs_i(INT_MAX) == abs_l(INT_MAX as long)");
	TEST_ASSERT(abs_i(I32_MIN) == abs_l((t_i64)I32_MIN), 
		"abs_i(INT_MIN) == abs_l(INT_MIN as long)");
}

// ============================================================================
// PRIME NUMBER TESTS - is_prime_u
// ============================================================================

void test_is_prime_i(void)
{
	TEST_START("is_prime_u - prime number check for 32-bit integers");
	
	// Prime numbers
	TEST_ASSERT(is_prime_u(3) == TRUE, "3 is prime");
	TEST_ASSERT(is_prime_u(5) == TRUE, "5 is prime");
	TEST_ASSERT(is_prime_u(7) == TRUE, "7 is prime");
	TEST_ASSERT(is_prime_u(11) == TRUE, "11 is prime");
	TEST_ASSERT(is_prime_u(13) == TRUE, "13 is prime");
	TEST_ASSERT(is_prime_u(17) == TRUE, "17 is prime");
	TEST_ASSERT(is_prime_u(97) == TRUE, "97 is prime");
	TEST_ASSERT(is_prime_u(101) == TRUE, "101 is prime");
	
	// Non-prime numbers
	TEST_ASSERT(is_prime_u(0) == FALSE, "0 is not prime");
	TEST_ASSERT(is_prime_u(1) == FALSE, "1 is not prime");
	TEST_ASSERT(is_prime_u(2) == FALSE, "2 is not prime (edge case)");
	TEST_ASSERT(is_prime_u(4) == FALSE, "4 is not prime");
	TEST_ASSERT(is_prime_u(6) == FALSE, "6 is not prime");
	TEST_ASSERT(is_prime_u(8) == FALSE, "8 is not prime");
	TEST_ASSERT(is_prime_u(9) == FALSE, "9 is not prime");
	TEST_ASSERT(is_prime_u(10) == FALSE, "10 is not prime");
	TEST_ASSERT(is_prime_u(100) == FALSE, "100 is not prime");
	TEST_ASSERT(is_prime_u(1000) == FALSE, "1000 is not prime");
}

// ============================================================================
// PRIME NUMBER TESTS - is_prime_l
// ============================================================================

void test_is_prime_l(void)
{
	TEST_START("is_prime_l - prime number check for 64-bit integers");
	
	// Prime numbers
	TEST_ASSERT(is_prime_l(3L) == TRUE, "3L is prime");
	TEST_ASSERT(is_prime_l(5L) == TRUE, "5L is prime");
	TEST_ASSERT(is_prime_l(7L) == TRUE, "7L is prime");
	TEST_ASSERT(is_prime_l(11L) == TRUE, "11L is prime");
	TEST_ASSERT(is_prime_l(97L) == TRUE, "97L is prime");
	TEST_ASSERT(is_prime_l(101L) == TRUE, "101L is prime");
	
	// Non-prime numbers
	TEST_ASSERT(is_prime_l(0L) == FALSE, "0L is not prime");
	TEST_ASSERT(is_prime_l(1L) == FALSE, "1L is not prime");
	TEST_ASSERT(is_prime_l(2L) == FALSE, "2L is not prime (edge case)");
	TEST_ASSERT(is_prime_l(4L) == FALSE, "4L is not prime");
	TEST_ASSERT(is_prime_l(6L) == FALSE, "6L is not prime");
	TEST_ASSERT(is_prime_l(100L) == FALSE, "100L is not prime");
	TEST_ASSERT(is_prime_l(1000L) == FALSE, "1000L is not prime");
	
	// Large numbers
	TEST_ASSERT(is_prime_l(1000000L) == FALSE, "1000000L is not prime");
}

// ============================================================================
// POWER TESTS - pow_i
// ============================================================================

void test_pow_i(void)
{
	TEST_START("pow_i - power function for 32-bit integers");
	
	// Power of 0
	TEST_ASSERT(pow_i(2, 0) == 1, "2^0 = 1");
	TEST_ASSERT(pow_i(10, 0) == 1, "10^0 = 1");
	TEST_ASSERT(pow_i(0, 0) == 1, "0^0 = 1");
	
	// Power of 1
	TEST_ASSERT(pow_i(2, 1) == 2, "2^1 = 2");
	TEST_ASSERT(pow_i(10, 1) == 10, "10^1 = 10");
	TEST_ASSERT(pow_i(5, 1) == 5, "5^1 = 5");
	
	// Small powers
	TEST_ASSERT(pow_i(2, 2) == 4, "2^2 = 4");
	TEST_ASSERT(pow_i(2, 3) == 8, "2^3 = 8");
	TEST_ASSERT(pow_i(2, 4) == 16, "2^4 = 16");
	TEST_ASSERT(pow_i(2, 10) == 1024, "2^10 = 1024");
	TEST_ASSERT(pow_i(3, 2) == 9, "3^2 = 9");
	TEST_ASSERT(pow_i(3, 3) == 27, "3^3 = 27");
	TEST_ASSERT(pow_i(5, 2) == 25, "5^2 = 25");
	TEST_ASSERT(pow_i(10, 2) == 100, "10^2 = 100");
	TEST_ASSERT(pow_i(10, 3) == 1000, "10^3 = 1000");
	
	// Zero base
	TEST_ASSERT(pow_i(0, 1) == 0, "0^1 = 0");
	TEST_ASSERT(pow_i(0, 5) == 0, "0^5 = 0");
	
	// Negative base
	TEST_ASSERT(pow_i(-2, 2) == 4, "(-2)^2 = 4");
	TEST_ASSERT(pow_i(-2, 3) == (t_u32)-8, "(-2)^3 = -8 (as unsigned)");
	TEST_ASSERT(pow_i(-3, 2) == 9, "(-3)^2 = 9");
}

// ============================================================================
// POWER TESTS - pow_l
// ============================================================================

void test_pow_l(void)
{
	TEST_START("pow_l - power function for 64-bit integers");
	
	// Power of 0
	TEST_ASSERT(pow_l(2L, 0) == 1UL, "2L^0 = 1");
	TEST_ASSERT(pow_l(10L, 0) == 1UL, "10L^0 = 1");
	TEST_ASSERT(pow_l(0L, 0) == 1UL, "0L^0 = 1");
	
	// Power of 1
	TEST_ASSERT(pow_l(2L, 1) == 2UL, "2L^1 = 2");
	TEST_ASSERT(pow_l(10L, 1) == 10UL, "10L^1 = 10");
	TEST_ASSERT(pow_l(5L, 1) == 5UL, "5L^1 = 5");
	
	// Small powers
	TEST_ASSERT(pow_l(2L, 2) == 4UL, "2L^2 = 4");
	TEST_ASSERT(pow_l(2L, 3) == 8UL, "2L^3 = 8");
	TEST_ASSERT(pow_l(2L, 10) == 1024UL, "2L^10 = 1024");
	TEST_ASSERT(pow_l(3L, 2) == 9UL, "3L^2 = 9");
	TEST_ASSERT(pow_l(3L, 3) == 27UL, "3L^3 = 27");
	TEST_ASSERT(pow_l(10L, 2) == 100UL, "10L^2 = 100");
	TEST_ASSERT(pow_l(10L, 3) == 1000UL, "10L^3 = 1000");
	
	// Larger powers
	TEST_ASSERT(pow_l(2L, 20) == 1048576UL, "2L^20 = 1048576");
	TEST_ASSERT(pow_l(10L, 5) == 100000UL, "10L^5 = 100000");
	
	// Zero base
	TEST_ASSERT(pow_l(0L, 1) == 0UL, "0L^1 = 0");
	TEST_ASSERT(pow_l(0L, 5) == 0UL, "0L^5 = 0");
	
	// Negative base
	TEST_ASSERT(pow_l(-2L, 2) == 4UL, "(-2L)^2 = 4");
	TEST_ASSERT(pow_l(-3L, 2) == 9UL, "(-3L)^2 = 9");
}

// ============================================================================
// ABSOLUTE VALUE TESTS - abs_f
// ============================================================================

void test_abs_f(void)
{
	TEST_START("abs_f - absolute value for floats");
	
	// Positive numbers
	TEST_ASSERT(abs_f(0.0f) == 0.0f, "abs(0.0f) returns 0.0f");
	TEST_ASSERT(abs_f(1.0f) == 1.0f, "abs(1.0f) returns 1.0f");
	TEST_ASSERT(abs_f(42.5f) == 42.5f, "abs(42.5f) returns 42.5f");
	TEST_ASSERT(abs_f(3.14159f) == 3.14159f, "abs(3.14159f) returns 3.14159f");
	
	// Negative numbers
	TEST_ASSERT(abs_f(-1.0f) == 1.0f, "abs(-1.0f) returns 1.0f");
	TEST_ASSERT(abs_f(-42.5f) == 42.5f, "abs(-42.5f) returns 42.5f");
	TEST_ASSERT(abs_f(-3.14159f) == 3.14159f, "abs(-3.14159f) returns 3.14159f");
	
	// Small values
	TEST_ASSERT(abs_f(0.001f) == 0.001f, "abs(0.001f) correct");
	TEST_ASSERT(abs_f(-0.001f) == 0.001f, "abs(-0.001f) correct");
}

// ============================================================================
// MAX TESTS
// ============================================================================

void test_max_functions(void)
{
	TEST_START("max_i32, max_u32, max_f32 - maximum value functions");
	
	// max_i32
	TEST_ASSERT(max_i32(5, 10) == 10, "max_i32(5, 10) = 10");
	TEST_ASSERT(max_i32(10, 5) == 10, "max_i32(10, 5) = 10");
	TEST_ASSERT(max_i32(-5, -10) == -5, "max_i32(-5, -10) = -5");
	TEST_ASSERT(max_i32(0, 0) == 0, "max_i32(0, 0) = 0");
	TEST_ASSERT(max_i32(I32_MAX, I32_MIN) == I32_MAX, "max_i32(MAX, MIN) = MAX");
	
	// max_u32
	TEST_ASSERT(max_u32(5U, 10U) == 10U, "max_u32(5, 10) = 10");
	TEST_ASSERT(max_u32(10U, 5U) == 10U, "max_u32(10, 5) = 10");
	TEST_ASSERT(max_u32(0U, 0U) == 0U, "max_u32(0, 0) = 0");
	TEST_ASSERT(max_u32(U32_MAX, 0U) == U32_MAX, "max_u32(MAX, 0) = MAX");
	
	// max_f32
	TEST_ASSERT(max_f32(5.5f, 10.5f) == 10.5f, "max_f32(5.5, 10.5) = 10.5");
	TEST_ASSERT(max_f32(10.5f, 5.5f) == 10.5f, "max_f32(10.5, 5.5) = 10.5");
	TEST_ASSERT(max_f32(-5.5f, -10.5f) == -5.5f, "max_f32(-5.5, -10.5) = -5.5");
	TEST_ASSERT(max_f32(0.0f, 0.0f) == 0.0f, "max_f32(0.0, 0.0) = 0.0");
}

// ============================================================================
// MIN TESTS
// ============================================================================

void test_min_functions(void)
{
	TEST_START("min_i32, min_u32, min_f32 - minimum value functions");
	
	// min_i32
	TEST_ASSERT(min_i32(5, 10) == 5, "min_i32(5, 10) = 5");
	TEST_ASSERT(min_i32(10, 5) == 5, "min_i32(10, 5) = 5");
	TEST_ASSERT(min_i32(-5, -10) == -10, "min_i32(-5, -10) = -10");
	TEST_ASSERT(min_i32(0, 0) == 0, "min_i32(0, 0) = 0");
	TEST_ASSERT(min_i32(I32_MAX, I32_MIN) == I32_MIN, "min_i32(MAX, MIN) = MIN");
	
	// min_u32
	TEST_ASSERT(min_u32(5U, 10U) == 5U, "min_u32(5, 10) = 5");
	TEST_ASSERT(min_u32(10U, 5U) == 5U, "min_u32(10, 5) = 5");
	TEST_ASSERT(min_u32(0U, 0U) == 0U, "min_u32(0, 0) = 0");
	TEST_ASSERT(min_u32(U32_MAX, 0U) == 0U, "min_u32(MAX, 0) = 0");
	
	// min_f32
	TEST_ASSERT(min_f32(5.5f, 10.5f) == 5.5f, "min_f32(5.5, 10.5) = 5.5");
	TEST_ASSERT(min_f32(10.5f, 5.5f) == 5.5f, "min_f32(10.5, 5.5) = 5.5");
	TEST_ASSERT(min_f32(-5.5f, -10.5f) == -10.5f, "min_f32(-5.5, -10.5) = -10.5");
	TEST_ASSERT(min_f32(0.0f, 0.0f) == 0.0f, "min_f32(0.0, 0.0) = 0.0");
}

// ============================================================================
// POWER TESTS - pow_u and pow_f
// ============================================================================

void test_pow_u(void)
{
	TEST_START("pow_u - power function for unsigned 32-bit integers");
	
	// Power of 0
	TEST_ASSERT(pow_u(2U, 0) == 1U, "2^0 = 1");
	TEST_ASSERT(pow_u(10U, 0) == 1U, "10^0 = 1");
	TEST_ASSERT(pow_u(0U, 0) == 1U, "0^0 = 1");
	
	// Power of 1
	TEST_ASSERT(pow_u(2U, 1) == 2U, "2^1 = 2");
	TEST_ASSERT(pow_u(10U, 1) == 10U, "10^1 = 10");
	
	// Small powers
	TEST_ASSERT(pow_u(2U, 2) == 4U, "2^2 = 4");
	TEST_ASSERT(pow_u(2U, 10) == 1024U, "2^10 = 1024");
	TEST_ASSERT(pow_u(3U, 3) == 27U, "3^3 = 27");
	TEST_ASSERT(pow_u(10U, 3) == 1000U, "10^3 = 1000");
	
	// Zero base
	TEST_ASSERT(pow_u(0U, 5) == 0U, "0^5 = 0");
}

void test_pow_f(void)
{
	TEST_START("pow_f - power function for floats");
	
	// Power of 0
	TEST_ASSERT(pow_f(2.0f, 0) == 1.0f, "2.0^0 = 1.0");
	TEST_ASSERT(pow_f(0.0f, 0) == 1.0f, "0.0^0 = 1.0");
	
	// Power of 1
	TEST_ASSERT(pow_f(2.5f, 1) == 2.5f, "2.5^1 = 2.5");
	
	// Small powers
	TEST_ASSERT(pow_f(2.0f, 2) == 4.0f, "2.0^2 = 4.0");
	TEST_ASSERT(pow_f(2.0f, 3) == 8.0f, "2.0^3 = 8.0");
	TEST_ASSERT(pow_f(1.5f, 2) >= 2.24f && pow_f(1.5f, 2) <= 2.26f, "1.5^2 ≈ 2.25");
	
	// Zero base
	TEST_ASSERT(pow_f(0.0f, 5) == 0.0f, "0.0^5 = 0.0");
}

// ============================================================================
// SQRT TESTS
// ============================================================================

void test_sqrt_functions(void)
{
	TEST_START("sqrt_f, sqrt_u - square root functions");
	
	// sqrt_f
	TEST_ASSERT(sqrt_f(0.0f) == 0.0f, "sqrt(0.0) = 0.0");
	TEST_ASSERT(sqrt_f(1.0f) == 1.0f, "sqrt(1.0) = 1.0");
	TEST_ASSERT(sqrt_f(4.0f) >= 1.99f && sqrt_f(4.0f) <= 2.01f, "sqrt(4.0) ≈ 2.0");
	TEST_ASSERT(sqrt_f(9.0f) >= 2.99f && sqrt_f(9.0f) <= 3.01f, "sqrt(9.0) ≈ 3.0");
	TEST_ASSERT(sqrt_f(16.0f) >= 3.99f && sqrt_f(16.0f) <= 4.01f, "sqrt(16.0) ≈ 4.0");
	TEST_ASSERT(sqrt_f(25.0f) >= 4.99f && sqrt_f(25.0f) <= 5.01f, "sqrt(25.0) ≈ 5.0");
	
	// sqrt_u
	TEST_ASSERT(sqrt_u(0U) == 0.0f, "sqrt(0U) = 0.0");
	TEST_ASSERT(sqrt_u(1U) >= 0.99f && sqrt_u(1U) <= 1.01f, "sqrt(1U) ≈ 1.0");
	TEST_ASSERT(sqrt_u(4U) >= 1.99f && sqrt_u(4U) <= 2.01f, "sqrt(4U) ≈ 2.0");
	TEST_ASSERT(sqrt_u(100U) >= 9.99f && sqrt_u(100U) <= 10.01f, "sqrt(100U) ≈ 10.0");
}

// ============================================================================
// ROUNDING TESTS
// ============================================================================

void test_rounding_functions(void)
{
	TEST_START("round_float, floor_float, ceil_float - rounding functions");
	
	// round_float
	TEST_ASSERT(round_float(0.0f) == 0, "round(0.0) = 0");
	TEST_ASSERT(round_float(0.4f) == 0, "round(0.4) = 0");
	TEST_ASSERT(round_float(0.5f) == 1, "round(0.5) = 1");
	TEST_ASSERT(round_float(0.6f) == 1, "round(0.6) = 1");
	TEST_ASSERT(round_float(1.4f) == 1, "round(1.4) = 1");
	TEST_ASSERT(round_float(1.5f) == 2, "round(1.5) = 2");
	TEST_ASSERT(round_float(-0.4f) == 0, "round(-0.4) = 0");
	TEST_ASSERT(round_float(-0.5f) == -1, "round(-0.5) = -1");
	TEST_ASSERT(round_float(-1.5f) == -2, "round(-1.5) = -2");
	
	// floor_float
	TEST_ASSERT(floor_float(0.0f) == 0, "floor(0.0) = 0");
	TEST_ASSERT(floor_float(0.9f) == 0, "floor(0.9) = 0");
	TEST_ASSERT(floor_float(1.0f) == 1, "floor(1.0) = 1");
	TEST_ASSERT(floor_float(1.9f) == 1, "floor(1.9) = 1");
	TEST_ASSERT(floor_float(-0.1f) == -1, "floor(-0.1) = -1");
	TEST_ASSERT(floor_float(-1.9f) == -2, "floor(-1.9) = -2");
	
	// ceil_float
	TEST_ASSERT(ceil_float(0.0f) == 0, "ceil(0.0) = 0");
	TEST_ASSERT(ceil_float(0.1f) == 1, "ceil(0.1) = 1");
	TEST_ASSERT(ceil_float(1.0f) == 1, "ceil(1.0) = 1");
	TEST_ASSERT(ceil_float(1.1f) == 2, "ceil(1.1) = 2");
	TEST_ASSERT(ceil_float(-0.9f) == 0, "ceil(-0.9) = 0");
	TEST_ASSERT(ceil_float(-1.1f) == -1, "ceil(-1.1) = -1");
}

// ============================================================================
// MAIN TEST RUNNER
// ============================================================================

void run_math_comprehensive_tests(void)
{	
	test_abs_i();
	test_abs_l();
	test_abs_f();
	test_abs_comparison();
	test_is_prime_i();
	test_is_prime_l();
	test_pow_i();
	test_pow_l();
	test_pow_u();
	test_pow_f();
	test_max_functions();
	test_min_functions();
	test_sqrt_functions();
	test_rounding_functions();
	
	TEST_SUMMARY();
}
