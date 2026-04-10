/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_wrapper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: GitHub Copilot                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 00:00:00 by Copilot           #+#    #+#             */
/*   Updated: 2026/02/03 00:00:00 by Copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Malloc Wrapper for Failure Testing
 * 
 * This file provides a wrapper around the standard malloc() function
 * that allows controlled failure for testing purposes. It uses the
 * LD_PRELOAD mechanism or link-time wrapping to intercept malloc calls.
 * 
 * When malloc failure testing is enabled:
 * - Counts all malloc() calls
 * - Can be configured to fail after N successful allocations
 * - Returns NULL to simulate allocation failure
 * - Tracks statistics about calls and failures
 * 
 * Build with: -Wl,--wrap=malloc or LD_PRELOAD
 */

#include <stdlib.h>
#include <stddef.h>

// Global control variables for malloc failure testing
int g_malloc_fail_enabled = 0;      // Whether failure testing is active
int g_malloc_fail_countdown = -1;   // Fail when this reaches 0
int g_malloc_call_count = 0;        // Total malloc calls made
int g_malloc_fail_count = 0;        // How many times malloc failed

// Forward declaration of real malloc (provided by libc)
void *__real_malloc(size_t size);

/**
 * __wrap_malloc - Wrapper function for malloc with failure injection
 * 
 * This function is called instead of the real malloc when linked with
 * -Wl,--wrap=malloc. It checks if failure testing is enabled and whether
 * it's time to fail, then either returns NULL or calls the real malloc.
 * 
 * @param size: Number of bytes to allocate
 * @return: Pointer to allocated memory, or NULL on failure/injection
 */
void *__wrap_malloc(size_t size)
{
	// If failure testing is not enabled, just use real malloc
	if (!g_malloc_fail_enabled)
		return __real_malloc(size);
	
	// Increment call counter
	g_malloc_call_count++;
	
	// Check if we should fail this allocation
	if (g_malloc_fail_countdown >= 0)
	{
		if (g_malloc_fail_countdown == 0)
		{
			// Time to fail!
			g_malloc_fail_count++;
			return NULL;
		}
		// Decrement countdown
		g_malloc_fail_countdown--;
	}
	
	// Proceed with real malloc
	return __real_malloc(size);
}

/**
 * __wrap_calloc - Wrapper function for calloc with failure injection
 * 
 * Similar to malloc wrapper, but for calloc. This ensures consistency
 * in failure testing across all allocation functions.
 * 
 * @param nmemb: Number of elements
 * @param size: Size of each element
 * @return: Pointer to allocated zeroed memory, or NULL on failure
 */
void *__real_calloc(size_t nmemb, size_t size);

void *__wrap_calloc(size_t nmemb, size_t size)
{
	// If failure testing is not enabled, just use real calloc
	if (!g_malloc_fail_enabled)
		return __real_calloc(nmemb, size);
	
	// Increment call counter (calloc counts as a malloc call)
	g_malloc_call_count++;
	
	// Check if we should fail this allocation
	if (g_malloc_fail_countdown >= 0)
	{
		if (g_malloc_fail_countdown == 0)
		{
			// Time to fail!
			g_malloc_fail_count++;
			return NULL;
		}
		// Decrement countdown
		g_malloc_fail_countdown--;
	}
	
	// Proceed with real calloc
	return __real_calloc(nmemb, size);
}

/**
 * __wrap_realloc - Wrapper function for realloc with failure injection
 * 
 * @param ptr: Pointer to previously allocated memory (or NULL)
 * @param size: New size for the allocation
 * @return: Pointer to reallocated memory, or NULL on failure
 */
void *__real_realloc(void *ptr, size_t size);

void *__wrap_realloc(void *ptr, size_t size)
{
	// If failure testing is not enabled, just use real realloc
	if (!g_malloc_fail_enabled)
		return __real_realloc(ptr, size);
	
	// Increment call counter (realloc counts as a malloc call)
	g_malloc_call_count++;
	
	// Check if we should fail this allocation
	if (g_malloc_fail_countdown >= 0)
	{
		if (g_malloc_fail_countdown == 0)
		{
			// Time to fail!
			g_malloc_fail_count++;
			return NULL;
		}
		// Decrement countdown
		g_malloc_fail_countdown--;
	}
	
	// Proceed with real realloc
	return __real_realloc(ptr, size);
}
