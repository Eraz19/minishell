/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_malloc_failure_example.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: GitHub Copilot                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 00:00:00 by Copilot           #+#    #+#             */
/*   Updated: 2026/02/03 00:00:00 by Copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Example Test File: Malloc Failure Testing
 * 
 * This file demonstrates how to use the malloc failure testing system
 * to verify that your libft functions properly handle allocation failures.
 * 
 * Key Concepts:
 * 1. Enable malloc failure testing with malloc_fail_enable()
 * 2. Set failure point with malloc_fail_after(n)
 * 3. Test your function and verify it returns NULL or handles error
 * 4. Disable with malloc_fail_disable()
 * 
 * The system works by wrapping malloc() at link time using --wrap flag.
 * When enabled, it counts malloc calls and can be configured to fail
 * at specific points to test error handling.
 */

#include "libft_test.h"
#include "libft.h"

// Use external test counters
extern int g_tests_run;
extern int g_tests_passed;
extern int g_tests_failed;
extern int g_list_tests_run;
extern int g_list_tests_passed;
extern int g_list_tests_failed;

// Override TEST_ASSERT to use string-specific counters for these tests
#undef TEST_ASSERT
#define TEST_ASSERT STR_TEST_ASSERT

// ============================================================================
// EXAMPLE 1: Testing a Simple String Creation
// ============================================================================

/**
 * Example of testing dstr_c with malloc failure.
 * Your dstr_c should return a dstr with s=NULL when malloc fails.
 */
void test_dstr_c_malloc_failure(void)
{
	TEST_START("dstr_c handles malloc failure");
	
	// Test: when malloc fails immediately (0 successful allocations)
	malloc_fail_enable();
	malloc_fail_after(0);  // Fail the very first malloc
	
	t_dstr result = dstr_c(cstr("Hello, World!"));
	
	// According to your function documentation, it should return NULL on failure
	STR_TEST_ASSERT(result.s == NULL, "dstr_c returns NULL when malloc fails");
	STR_TEST_ASSERT(result.len == 0, "dstr_c sets len to 0 on failure");
	
	malloc_fail_disable();
}

// ============================================================================
// EXAMPLE 2: Testing a Function with Single Allocation
// ============================================================================

/**
 * Example of testing str_repeat which allocates once.
 */
void test_str_repeat_malloc_failure(void)
{
	TEST_START("str_repeat handles malloc failure");
	
	malloc_fail_enable();
	malloc_fail_after(0);
	
	t_dstr result = str_repeat(cstr("test"), 10);
	
	STR_TEST_ASSERT(result.s == NULL, "Returns NULL when malloc fails");
	STR_TEST_ASSERT(result.len == 0, "Sets len to 0 on failure");
	
	malloc_fail_disable();
}

// ============================================================================
// EXAMPLE 3: Testing a Function that Might Do Multiple Allocations
// ============================================================================

/**
 * Example of testing str_split which may do multiple allocations.
 * We test failure at different points to ensure proper cleanup.
 */
void test_str_split_malloc_failure(void)
{
	TEST_START("str_split handles malloc failure at various points");
	
	t_cstr input = cstr("hello,world,test");
	
	// Test 1: Fail on first allocation 
	malloc_fail_enable();
	malloc_fail_after(0);
	
	t_dstr_arr result = str_split(input, ',', NULL);
	STR_TEST_ASSERT(result.strs == NULL, "Returns NULL strs when first malloc fails");
	STR_TEST_ASSERT(result.len == 0, "Sets len to 0 on failure");
	
	malloc_fail_disable();
	
	// Test 2: Fail on second allocation
	malloc_fail_enable();
	malloc_fail_after(1);  // Let first malloc succeed, fail second
	
	result = str_split(input, ',', NULL);
	STR_TEST_ASSERT(result.strs == NULL, "Returns NULL and cleans up when second malloc fails");
	
	malloc_fail_disable();
}

// ============================================================================
// EXAMPLE 4: Testing List Node Creation
// ============================================================================

/**
 * Example of testing node creation with malloc failure.
 */
void test_node_malloc_failure(void)
{
	TEST_START("node handles malloc failure");
	
	int value = 42;
	int *ptr = &value;
	
	// Test: node should return NULL when malloc fails
	malloc_fail_enable();
	malloc_fail_after(0);
	
	t_node *n = node(ptr);
	
	LIST_TEST_ASSERT(n == NULL, "node returns NULL when malloc fails");
	
	malloc_fail_disable();
}

// ============================================================================
// EXAMPLE 5: Testing dstr_s with Macro
// ============================================================================

/**
 * Example using TEST_MALLOC_FAIL_POINT macro for cleaner tests.
 */
void test_dstr_s_malloc_failure_macro(void)
{
	TEST_START("dstr_s handles malloc failure (using macro)");
	
	// The macro handles enable/disable for you
	TEST_MALLOC_FAIL_POINT("dstr_s returns NULL on malloc fail", 0, {
		t_dstr result = dstr_s(100);
		STR_TEST_ASSERT(result.s == NULL, "dstr_s malloc failure");
		// Note: if result.s is not NULL, you should free it
		if (result.s != NULL)
			free(result.s);
	});
}

// ============================================================================
// EXAMPLE 6: Testing with Multiple Failure Points
// ============================================================================

/**
 * Advanced example: test function with multiple allocations
 * at each possible failure point.
 */
void test_lst_insert_malloc_failures(void)
{
	TEST_START("lst_insert handles malloc failures at all points");
	
	t_lst list = lst_();
	int value = 42;
	int *ptr = malloc(sizeof(int));
	*ptr = value;
	
	// Test each potential allocation failure point
	for (int fail_point = 0; fail_point < 3; fail_point++)
	{
		malloc_fail_enable();
		malloc_fail_after(fail_point);
		
		t_node *n = node(ptr);
		t_lst result = lst_insert(&list, n, 0);
		
		if (malloc_get_fail_count() > 0)
		{
			// Malloc failed, verify proper error handling
			LIST_TEST_ASSERT(result.nodes == NULL || result.size == list.size,
				"lst_insert handles malloc failure gracefully");
			
			// Clean up if node wasn't inserted
			if (n != NULL && (result.size == 0 || result.nodes == NULL))
			{
				free(n);
			}
		}
		
		malloc_fail_disable();
		
		// Stop if we didn't reach this allocation point
		if (malloc_get_call_count() <= fail_point)
			break;
	}
	
	free(ptr);
	free_lst(&list, NULL);
}

// ============================================================================
// MAIN RUNNER (for demonstration purposes)
// ============================================================================

/**
 * This demonstrates how to integrate malloc failure tests into your suite.
 * Called from test_main.c as part of the complete test suite.
 */
void run_malloc_failure_examples(void)
{
	TEST_HEADER("Malloc Failure Testing Examples");
	
	test_dstr_c_malloc_failure();
	test_str_repeat_malloc_failure();
	test_str_split_malloc_failure();
	test_node_malloc_failure();
	test_dstr_s_malloc_failure_macro();
	test_lst_insert_malloc_failures();
	
	// Summary is printed by test_main.c for string and list tests
}

/**
 * INTEGRATION NOTES:
 * 
 * To add malloc failure tests to your existing test suite:
 * 
 * 1. In your test files (e.g., test_string_comprehensive.c):
 *    - Add test functions that use malloc_fail_enable/disable
 *    - Use malloc_fail_after(n) to control when malloc fails
 *    - Verify your functions return appropriate error values
 * 
 * 2. The build system automatically links with malloc wrapper
 *    - No need to modify compile commands
 *    - The -Wl,--wrap=malloc flag is already in Makefile
 * 
 * 3. Best practices:
 *    - Always disable malloc failure testing after your test
 *    - Test failure at each allocation point in multi-alloc functions
 *    - Verify no memory leaks even when malloc fails
 *    - Check that functions return documented error values (NULL, empty, etc.)
 * 
 * 4. What to test:
 *    - Functions that allocate memory (str_dup, dstr_s, node, etc.)
 *    - Functions with multiple allocations (str_split, lst_insert, etc.)
 *    - Functions that should clean up on partial failure
 *    - Edge cases where malloc might fail (large allocations, etc.)
 */
