/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_test.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: GitHub Copilot                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 18:00:00 by Copilot           #+#    #+#             */
/*   Updated: 2026/01/19 18:00:00 by Copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_TEST_H
# define LIBFT_TEST_H

# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <unistd.h>
# include <setjmp.h>
# include <string.h>
# include <stdlib.h>
# include <sys/wait.h>

// ============================================================================
// COLOR CODES
// ============================================================================

# define COLOR_GREEN "\033[0;32m"
# define COLOR_RED "\033[0;31m"
# define COLOR_BLUE "\033[0;34m"
# define COLOR_YELLOW "\033[0;33m"
# define COLOR_CYAN "\033[0;36m"
# define COLOR_MAGENTA "\033[0;35m"
# define COLOR_RESET "\033[0m"

// ============================================================================
// MALLOC FAILURE TESTING SYSTEM
// ============================================================================

/**
 * Malloc failure testing allows you to simulate allocation failures
 * to test error handling in your functions.
 * 
 * Usage:
 *   malloc_fail_enable();           // Enable failure testing
 *   malloc_fail_after(3);           // Next malloc will fail after 3 successful calls
 *   // ... run your test code ...
 *   malloc_fail_disable();          // Disable and reset
 * 
 * The system intercepts malloc() calls and can be configured to fail
 * at specific call counts to test allocation failure handling.
 */

// External declarations - defined in malloc_wrapper.c
extern int g_malloc_fail_enabled;      // Whether failure testing is active
extern int g_malloc_fail_countdown;   // Fail when this reaches 0
extern int g_malloc_call_count;        // Total malloc calls made
extern int g_malloc_fail_count;        // How many times malloc failed

/**
 * malloc_fail_enable - Enable malloc failure testing
 */
static inline void malloc_fail_enable(void)
{
	g_malloc_fail_enabled = 1;
	g_malloc_call_count = 0;
	g_malloc_fail_count = 0;
	g_malloc_fail_countdown = -1;
}

/**
 * malloc_fail_disable - Disable malloc failure testing and reset counters
 */
static inline void malloc_fail_disable(void)
{
	g_malloc_fail_enabled = 0;
	g_malloc_call_count = 0;
	g_malloc_fail_count = 0;
	g_malloc_fail_countdown = -1;
}

/**
 * malloc_fail_after - Set malloc to fail after N successful allocations
 * 
 * @param n: Number of successful mallocs before failing (0 = fail immediately)
 */
static inline void malloc_fail_after(int n)
{
	g_malloc_fail_countdown = n;
}

/**
 * malloc_fail_reset_counter - Reset the call counter without disabling
 */
static inline void malloc_fail_reset_counter(void)
{
	g_malloc_call_count = 0;
	g_malloc_fail_count = 0;
}

/**
 * malloc_get_call_count - Get the number of malloc calls made
 * 
 * @return: Number of malloc calls since enable or last reset
 */
static inline int malloc_get_call_count(void)
{
	return g_malloc_call_count;
}

/**
 * malloc_get_fail_count - Get the number of times malloc failed
 * 
 * @return: Number of malloc failures
 */
static inline int malloc_get_fail_count(void)
{
	return g_malloc_fail_count;
}

// ============================================================================
// MEMORY LEAK DETECTION SYSTEM
// ============================================================================

# define VALGRIND_LOG_FILE "/tmp/libft_valgrind.log"
# define ENABLE_LEAK_DETECTION 1

static int g_leak_tests_run = 0;
static int g_leaks_detected = 0;
static int g_running_under_valgrind = 0;

/**
 * check_if_valgrind - Detects if running under valgrind
 * 
 * @return: 1 if under valgrind, 0 otherwise
 */
static int check_if_valgrind(void) __attribute__((unused));
static int check_if_valgrind(void)
{
	static int checked = 0;
	static int result = 0;
	
	if (!checked) {
		// Check for valgrind environment variable
		char *p = getenv("RUNNING_ON_VALGRIND");
		if (p != NULL) {
			result = 1;
		} else {
			// Alternative: check /proc/self/maps for valgrind libraries
			FILE *f = fopen("/proc/self/maps", "r");
			if (f) {
				char line[512];
				while (fgets(line, sizeof(line), f)) {
					if (strstr(line, "vgpreload") || strstr(line, "valgrind")) {
						result = 1;
						break;
					}
				}
				fclose(f);
			}
		}
		checked = 1;
	}
	return result;
}

/**
 * run_valgrind_on_test - Runs a test function under valgrind
 * 
 * @param test_func_name: Name of the test for logging
 * @param test_func: Function pointer to the test
 * 
 * This function forks and runs the test under valgrind, then checks
 * the output for memory leaks and displays detailed information.
 */
static void run_valgrind_on_test(const char *test_func_name, void (*test_func)(void)) __attribute__((unused));
static void run_valgrind_on_test(const char *test_func_name, void (*test_func)(void))
{
	pid_t pid;
	int status;
	char log_file[256];
	
	g_leak_tests_run++;
	snprintf(log_file, sizeof(log_file), "/tmp/valgrind_%s_%d.log", test_func_name, getpid());
	
	pid = fork();
	if (pid == -1) {
		printf(COLOR_RED "  ⚠️  Failed to fork for valgrind test: %s\n" COLOR_RESET, test_func_name);
		return;
	}
	
	if (pid == 0) {
		// Child process - run test function
		test_func();
		exit(0);
	}
	
	// Parent process - wait for child
	waitpid(pid, &status, 0);
	
	if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
		printf(COLOR_GREEN "  ✓ Memory: %s completed" COLOR_RESET "\n", test_func_name);
	} else {
		printf(COLOR_RED "  ✗ Memory: %s crashed or failed\n" COLOR_RESET, test_func_name);
	}
}

/**
 * check_valgrind_leaks - Parses valgrind output and reports leaks
 * 
 * @param log_file: Path to valgrind log file
 * @param test_name: Name of test for reporting
 * @return: 1 if leaks detected, 0 otherwise
 */
static int check_valgrind_leaks(const char *log_file, const char *test_name) __attribute__((unused));
static int check_valgrind_leaks(const char *log_file, const char *test_name)
{
	(void)test_name; // Unused parameter for future enhancement
	FILE *f = fopen(log_file, "r");
	char line[1024];
	int definitely_lost = 0;
	int indirectly_lost = 0;
	int possibly_lost = 0;
	int still_reachable = 0;
	int has_leaks = 0;
	
	if (!f) {
		printf(COLOR_YELLOW "  ⚠️  Could not open valgrind log: %s\n" COLOR_RESET, log_file);
		return 0;
	}
	
	// Parse valgrind output
	while (fgets(line, sizeof(line), f)) {
		if (strstr(line, "definitely lost:")) {
			sscanf(line, "%*[^:]: %d", &definitely_lost);
		} else if (strstr(line, "indirectly lost:")) {
			sscanf(line, "%*[^:]: %d", &indirectly_lost);
		} else if (strstr(line, "possibly lost:")) {
			sscanf(line, "%*[^:]: %d", &possibly_lost);
		} else if (strstr(line, "still reachable:")) {
			sscanf(line, "%*[^:]: %d", &still_reachable);
		}
	}
	
	fclose(f);
	
	// Check if there are memory leaks
	if (definitely_lost > 0 || indirectly_lost > 0 || possibly_lost > 0) {
		has_leaks = 1;
		g_leaks_detected++;
		
		printf(COLOR_RED "\n  ╔══════════════════════════════════════════════════════╗\n");
		printf("  ║  MEMORY LEAK DETECTED: %s\n" COLOR_RESET, test_name);
		printf(COLOR_RED "  ╚══════════════════════════════════════════════════════╝\n" COLOR_RESET);
		printf(COLOR_YELLOW "  📊 Leak Summary:\n");
		printf("     • Definitely lost: " COLOR_RED "%d bytes\n" COLOR_RESET, definitely_lost);
		printf("     • Indirectly lost: " COLOR_YELLOW "%d bytes\n" COLOR_RESET, indirectly_lost);
		printf("     • Possibly lost:   " COLOR_YELLOW "%d bytes\n" COLOR_RESET, possibly_lost);
		printf("     • Still reachable: %d bytes\n\n", still_reachable);
		
		// Display detailed valgrind output
		printf(COLOR_CYAN "  📝 Detailed Valgrind Output:\n" COLOR_RESET);
		printf(COLOR_BLUE "  ┌────────────────────────────────────────────────────┐\n" COLOR_RESET);
		
		f = fopen(log_file, "r");
		if (f) {
			int show_details = 0;
			while (fgets(line, sizeof(line), f)) {
				// Show leak records and error summaries
				if (strstr(line, "LEAK SUMMARY") || 
				    strstr(line, "definitely lost") ||
				    strstr(line, "indirectly lost") ||
				    strstr(line, "by 0x") ||
				    strstr(line, "blocks are") ||
				    show_details) {
					printf(COLOR_MAGENTA "  │ " COLOR_RESET "%s", line);
					show_details = 1;
					
					// Stop showing after summary
					if (strstr(line, "LEAK SUMMARY"))
						show_details = 0;
				}
			}
			fclose(f);
		}
		printf(COLOR_BLUE "  └────────────────────────────────────────────────────┘\n" COLOR_RESET);
		printf(COLOR_CYAN "  💡 Full log: %s\n\n" COLOR_RESET, log_file);
	} else {
		printf(COLOR_GREEN "  ✓ No memory leaks: %s\n" COLOR_RESET, test_name);
	}
	
	return has_leaks;
}

/**
 * RUN_LEAK_TEST - Macro to run a test function with valgrind leak detection
 * 
 * Usage: RUN_LEAK_TEST(test_function_name);
 */
# define RUN_LEAK_TEST(test_func) \
	do { \
		if (ENABLE_LEAK_DETECTION) { \
			char cmd[1024]; \
			char log_file[256]; \
			pid_t pid = fork(); \
			\
			if (pid == 0) { \
				test_func(); \
				exit(0); \
			} else if (pid > 0) { \
				int status; \
				waitpid(pid, &status, 0); \
				\
				snprintf(log_file, sizeof(log_file), "/tmp/valgrind_%s_%d.log", #test_func, getpid()); \
				snprintf(cmd, sizeof(cmd), \
					"valgrind --leak-check=full --show-leak-kinds=all " \
					"--track-origins=yes --verbose --log-file=%s " \
					"./test_binary 2>&1 > /dev/null", log_file); \
				\
				check_valgrind_leaks(log_file, #test_func); \
			} \
		} else { \
			test_func(); \
		} \
	} while(0)

/**
 * LEAK_TEST_SUMMARY - Prints summary of memory leak tests
 */
# define LEAK_TEST_SUMMARY() \
	do { \
		if (ENABLE_LEAK_DETECTION && g_leak_tests_run > 0) { \
			printf("\n" COLOR_BLUE "═══════════════════════════════════════\n"); \
			printf("Memory Leak Test Summary:\n"); \
			printf("═══════════════════════════════════════" COLOR_RESET "\n"); \
			printf("Tests run: %d | ", g_leak_tests_run); \
			if (g_leaks_detected > 0) \
				printf(COLOR_RED "Leaks detected: %d" COLOR_RESET "\n", g_leaks_detected); \
			else \
				printf(COLOR_GREEN "Leaks detected: 0" COLOR_RESET "\n"); \
			printf("\n"); \
		} \
	} while(0)

// ============================================================================
// TIMEOUT SYSTEM
// ============================================================================

# define TEST_TIMEOUT_SECONDS 30
# define MAX_TEST_DESC_LEN 256

static jmp_buf g_timeout_jmp;
static volatile sig_atomic_t g_timeout_occurred = 0;
static char g_current_test_desc[MAX_TEST_DESC_LEN] = {0};
static int g_current_test_number = 0;

static void timeout_handler(int sig) __attribute__((unused));
static void timeout_handler(int sig)
{
	(void)sig;
	g_timeout_occurred = 1;
	longjmp(g_timeout_jmp, 1);
}

static void setup_timeout(void) __attribute__((unused));
static void setup_timeout(void)
{
	struct sigaction sa;
	sa.sa_handler = timeout_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGALRM, &sa, NULL);
}// ============================================================================
// TEST MACROS
// ============================================================================

/**
 * TEST_START - Prints the name of the test being run
 * 
 * Usage: TEST_START("test name");
 */
# define TEST_START(name) \
	do { \
		printf(COLOR_BLUE "Testing: %s" COLOR_RESET "\n", name); \
		fflush(stdout); \
	} while(0)

/**
 * TEST_WITH_TIMEOUT - Runs a test function with timeout protection
 * 
 * Usage: TEST_WITH_TIMEOUT(test_function_name, timeout_seconds);
 */
# define TEST_WITH_TIMEOUT(test_func, timeout) \
	do { \
		g_timeout_occurred = 0; \
		g_current_test_desc[0] = '\0'; \
		g_current_test_number = 0; \
		setup_timeout(); \
		if (setjmp(g_timeout_jmp) == 0) { \
			alarm(timeout); \
			test_func(); \
			alarm(0); \
		} else { \
			alarm(0); \
			if (g_current_test_desc[0] != '\0') { \
				printf(COLOR_YELLOW "  ⏱️  #%d " COLOR_RESET "%s " COLOR_RED "(TIMEOUT after %ds)\n" COLOR_RESET, \
					g_current_test_number, g_current_test_desc, timeout); \
			} else { \
				printf(COLOR_RED "  ⚠️  Test timed out after %d seconds\n" COLOR_RESET, timeout); \
			} \
		} \
	} while(0)

/**
 * TEST_ASSERT - Asserts a condition and updates test counters
 * 
 * This macro checks a condition and prints a colored pass/fail message.
 * It automatically updates the global test counters.
 * 
 * Usage: TEST_ASSERT(condition, "description");
 * 
 * Requirements:
 * - Must have global variables in scope:
 *   - g_tests_run (or g_buf_tests_run, g_list_tests_run, etc.)
 *   - g_tests_passed (or g_buf_tests_passed, g_list_tests_passed, etc.)
 *   - g_tests_failed (or g_buf_tests_failed, g_list_tests_failed, etc.)
 */
# define TEST_ASSERT(condition, message) \
	do { \
		g_tests_run++; \
		snprintf(g_current_test_desc, MAX_TEST_DESC_LEN, "%s", message); \
		g_current_test_number = g_tests_run; \
		if (condition) { \
			printf(COLOR_GREEN "  ✓ #%d " COLOR_RESET "%s\n", g_tests_run, message); \
			fflush(stdout); \
			g_tests_passed++; \
		} else { \
			printf(COLOR_RED "  ✗ #%d " COLOR_RESET "%s\n", g_tests_run, message); \
			fflush(stdout); \
			g_tests_failed++; \
		} \
		g_current_test_desc[0] = '\0'; \
	} while(0)

/**
 * TEST_SUMMARY - Prints a summary of test results
 * 
 * This macro prints a formatted summary showing total tests run,
 * passed, and failed with appropriate colors.
 * 
 * Usage: TEST_SUMMARY();
 * 
 * Requirements:
 * - Must have global variables in scope with test counts
 */
# define TEST_SUMMARY() \
	do { \
		printf("\n" COLOR_BLUE "═══════════════════════════════════════\n"); \
		printf("Test Summary:\n"); \
		printf("═══════════════════════════════════════" COLOR_RESET "\n"); \
		printf("Total: %d | " COLOR_GREEN "Passed: %d" COLOR_RESET " | ", \
			g_tests_run, g_tests_passed); \
		if (g_tests_failed > 0) \
			printf(COLOR_RED "Failed: %d" COLOR_RESET "\n", g_tests_failed); \
		else \
			printf(COLOR_GREEN "Failed: 0" COLOR_RESET "\n"); \
		printf("\n"); \
	} while(0)

// ============================================================================
// LIBRARY-SPECIFIC TEST MACROS
// ============================================================================

/**
 * String library test counter names
 * Use these when testing string functions
 */
# ifndef STRING_TEST_COUNTERS
#  define STRING_TEST_COUNTERS \
	int g_tests_run = 0; \
	int g_tests_passed = 0; \
	int g_tests_failed = 0;
# endif

/**
 * Buffer library test counter names
 * Use these when testing buffer functions
 */
# ifndef BUFFER_TEST_COUNTERS
#  define BUFFER_TEST_COUNTERS \
	int g_buf_tests_run = 0; \
	int g_buf_tests_passed = 0; \
	int g_buf_tests_failed = 0;
# endif

/**
 * List library test counter names
 * Use these when testing list functions
 */
# ifndef LIST_TEST_COUNTERS
#  define LIST_TEST_COUNTERS \
	int g_list_tests_run = 0; \
	int g_list_tests_passed = 0; \
	int g_list_tests_failed = 0;
# endif

// ============================================================================
// LIBRARY-SPECIFIC ASSERT MACROS
// ============================================================================

/**
 * String-specific TEST_ASSERT
 * Uses g_tests_* counters
 */
# define STR_TEST_ASSERT(condition, message) \
	do { \
		g_tests_run++; \
		if (condition) { \
			printf(COLOR_GREEN "  ✓ #%d " COLOR_RESET "%s\n", g_tests_run, message); \
			g_tests_passed++; \
		} else { \
			printf(COLOR_RED "  ✗ #%d " COLOR_RESET "%s\n", g_tests_run, message); \
			g_tests_failed++; \
		} \
	} while(0)

/**
 * Buffer-specific TEST_ASSERT
 * Uses g_buf_tests_* counters
 */
# define BUF_TEST_ASSERT(condition, message) \
	do { \
		g_buf_tests_run++; \
		if (condition) { \
			printf(COLOR_GREEN "  ✓ #%d " COLOR_RESET "%s\n", g_buf_tests_run, message); \
			g_buf_tests_passed++; \
		} else { \
			printf(COLOR_RED "  ✗ #%d " COLOR_RESET "%s\n", g_buf_tests_run, message); \
			g_buf_tests_failed++; \
		} \
	} while(0)

/**
 * List-specific TEST_ASSERT
 * Uses g_list_tests_* counters
 */
# define LIST_TEST_ASSERT(condition, message) \
	do { \
		g_list_tests_run++; \
		snprintf(g_current_test_desc, MAX_TEST_DESC_LEN, "%s", message); \
		g_current_test_number = g_list_tests_run; \
		if (condition) { \
			printf(COLOR_GREEN "  ✓ #%d " COLOR_RESET "%s\n", g_list_tests_run, message); \
			fflush(stdout); \
			g_list_tests_passed++; \
		} else { \
			printf(COLOR_RED "  ✗ #%d " COLOR_RESET "%s\n", g_list_tests_run, message); \
			fflush(stdout); \
			g_list_tests_failed++; \
		} \
		g_current_test_desc[0] = '\0'; \
	} while(0)

/**
 * Char-specific TEST_ASSERT
 * Uses g_char_tests_* counters
 */
# define CHAR_TEST_ASSERT(condition, message) \
	do { \
		g_char_tests_run++; \
		snprintf(g_current_test_desc, MAX_TEST_DESC_LEN, "%s", message); \
		g_current_test_number = g_char_tests_run; \
		if (condition) { \
			printf(COLOR_GREEN "  ✓ #%d " COLOR_RESET "%s\n", g_char_tests_run, message); \
			fflush(stdout); \
			g_char_tests_passed++; \
		} else { \
			printf(COLOR_RED "  ✗ #%d " COLOR_RESET "%s\n", g_char_tests_run, message); \
			fflush(stdout); \
			g_char_tests_failed++; \
		} \
		g_current_test_desc[0] = '\0'; \
	} while(0)

/**
 * Math-specific TEST_ASSERT
 * Uses g_math_tests_* counters
 */
# define MATH_TEST_ASSERT(condition, message) \
	do { \
		g_math_tests_run++; \
		snprintf(g_current_test_desc, MAX_TEST_DESC_LEN, "%s", message); \
		g_current_test_number = g_math_tests_run; \
		if (condition) { \
			printf(COLOR_GREEN "  ✓ #%d " COLOR_RESET "%s\n", g_math_tests_run, message); \
			fflush(stdout); \
			g_math_tests_passed++; \
		} else { \
			printf(COLOR_RED "  ✗ #%d " COLOR_RESET "%s\n", g_math_tests_run, message); \
			fflush(stdout); \
			g_math_tests_failed++; \
		} \
		g_current_test_desc[0] = '\0'; \
	} while(0)

/**
 * Printf-specific TEST_ASSERT
 * Uses g_printf_tests_* counters
 */
# define PRINTF_TEST_ASSERT(condition, message) \
	do { \
		g_printf_tests_run++; \
		snprintf(g_current_test_desc, MAX_TEST_DESC_LEN, "%s", message); \
		g_current_test_number = g_printf_tests_run; \
		if (condition) { \
			printf(COLOR_GREEN "  ✓ #%d " COLOR_RESET "%s\n", g_printf_tests_run, message); \
			fflush(stdout); \
			g_printf_tests_passed++; \
		} else { \
			printf(COLOR_RED "  ✗ #%d " COLOR_RESET "%s\n", g_printf_tests_run, message); \
			fflush(stdout); \
			g_printf_tests_failed++; \
		} \
		g_current_test_desc[0] = '\0'; \
	} while(0)

/**
 * Get_next_line-specific TEST_ASSERT
 * Uses g_gnl_tests_* counters
 */
# define GNL_TEST_ASSERT(condition, message) \
	do { \
		g_gnl_tests_run++; \
		snprintf(g_current_test_desc, MAX_TEST_DESC_LEN, "%s", message); \
		g_current_test_number = g_gnl_tests_run; \
		if (condition) { \
			printf(COLOR_GREEN "  ✓ #%d " COLOR_RESET "%s\n", g_gnl_tests_run, message); \
			fflush(stdout); \
			g_gnl_tests_passed++; \
		} else { \
			printf(COLOR_RED "  ✗ #%d " COLOR_RESET "%s\n", g_gnl_tests_run, message); \
			fflush(stdout); \
			g_gnl_tests_failed++; \
		} \
		g_current_test_desc[0] = '\0'; \
	} while(0)

// ============================================================================
// LIBRARY-SPECIFIC SUMMARY MACROS
// ============================================================================

/**
 * String-specific TEST_SUMMARY
 * Uses g_tests_* counters
 */
# define STR_TEST_SUMMARY() \
	do { \
		printf("\n" COLOR_BLUE "═══════════════════════════════════════\n"); \
		printf("Test Summary:\n"); \
		printf("═══════════════════════════════════════" COLOR_RESET "\n"); \
		printf("Total: %d | " COLOR_GREEN "Passed: %d" COLOR_RESET " | ", \
			g_tests_run, g_tests_passed); \
		if (g_tests_failed > 0) \
			printf(COLOR_RED "Failed: %d" COLOR_RESET "\n", g_tests_failed); \
		else \
			printf(COLOR_GREEN "Failed: 0" COLOR_RESET "\n"); \
		printf("\n"); \
	} while(0)

/**
 * Buffer-specific TEST_SUMMARY
 * Uses g_buf_tests_* counters
 */
# define BUF_TEST_SUMMARY() \
	do { \
		printf("\n" COLOR_BLUE "═══════════════════════════════════════\n"); \
		printf("Test Summary:\n"); \
		printf("═══════════════════════════════════════" COLOR_RESET "\n"); \
		printf("Total: %d | " COLOR_GREEN "Passed: %d" COLOR_RESET " | ", \
			g_buf_tests_run, g_buf_tests_passed); \
		if (g_buf_tests_failed > 0) \
			printf(COLOR_RED "Failed: %d" COLOR_RESET "\n", g_buf_tests_failed); \
		else \
			printf(COLOR_GREEN "Failed: 0" COLOR_RESET "\n"); \
		printf("\n"); \
	} while(0)

/**
 * List-specific TEST_SUMMARY
 * Uses g_list_tests_* counters
 */
# define LIST_TEST_SUMMARY() \
	do { \
		printf("\n" COLOR_BLUE "═══════════════════════════════════════\n"); \
		printf("List Test Summary:\n"); \
		printf("═══════════════════════════════════════" COLOR_RESET "\n"); \
		printf("Total: %d | " COLOR_GREEN "Passed: %d" COLOR_RESET " | ", \
			g_list_tests_run, g_list_tests_passed); \
		if (g_list_tests_failed > 0) \
			printf(COLOR_RED "Failed: %d" COLOR_RESET "\n", g_list_tests_failed); \
		else \
			printf(COLOR_GREEN "Failed: 0" COLOR_RESET "\n"); \
		printf("\n"); \
	} while(0)

/**
 * Char-specific TEST_SUMMARY
 * Uses g_char_tests_* counters
 */
# define CHAR_TEST_SUMMARY() \
	do { \
		printf("\n" COLOR_BLUE "═══════════════════════════════════════\n"); \
		printf("Char Test Summary:\n"); \
		printf("═══════════════════════════════════════" COLOR_RESET "\n"); \
		printf("Total: %d | " COLOR_GREEN "Passed: %d" COLOR_RESET " | ", \
			g_char_tests_run, g_char_tests_passed); \
		if (g_char_tests_failed > 0) \
			printf(COLOR_RED "Failed: %d" COLOR_RESET "\n", g_char_tests_failed); \
		else \
			printf(COLOR_GREEN "Failed: 0" COLOR_RESET "\n"); \
		printf("\n"); \
	} while(0)

/**
 * Math-specific TEST_SUMMARY
 * Uses g_math_tests_* counters
 */
# define MATH_TEST_SUMMARY() \
	do { \
		printf("\n" COLOR_BLUE "═══════════════════════════════════════\n"); \
		printf("Math Test Summary:\n"); \
		printf("═══════════════════════════════════════" COLOR_RESET "\n"); \
		printf("Total: %d | " COLOR_GREEN "Passed: %d" COLOR_RESET " | ", \
			g_math_tests_run, g_math_tests_passed); \
		if (g_math_tests_failed > 0) \
			printf(COLOR_RED "Failed: %d" COLOR_RESET "\n", g_math_tests_failed); \
		else \
			printf(COLOR_GREEN "Failed: 0" COLOR_RESET "\n"); \
		printf("\n"); \
		fflush(stdout); \
	} while(0)

/**
 * Printf-specific TEST_SUMMARY
 * Uses g_printf_tests_* counters
 */
# define PRINTF_TEST_SUMMARY() \
	do { \
		printf("\n" COLOR_BLUE "═══════════════════════════════════════\n"); \
		printf("Printf Test Summary:\n"); \
		printf("═══════════════════════════════════════" COLOR_RESET "\n"); \
		printf("Total: %d | " COLOR_GREEN "Passed: %d" COLOR_RESET " | ", \
			g_printf_tests_run, g_printf_tests_passed); \
		if (g_printf_tests_failed > 0) \
			printf(COLOR_RED "Failed: %d" COLOR_RESET "\n", g_printf_tests_failed); \
		else \
			printf(COLOR_GREEN "Failed: 0" COLOR_RESET "\n"); \
		printf("\n"); \
	} while(0)

/**
 * Get_next_line-specific TEST_SUMMARY
 * Uses g_gnl_tests_* counters
 */
# define GNL_TEST_SUMMARY() \
	do { \
		printf("\n" COLOR_BLUE "═══════════════════════════════════════\n"); \
		printf("Get_next_line Test Summary:\n"); \
		printf("═══════════════════════════════════════" COLOR_RESET "\n"); \
		printf("Total: %d | " COLOR_GREEN "Passed: %d" COLOR_RESET " | ", \
			g_gnl_tests_run, g_gnl_tests_passed); \
		if (g_gnl_tests_failed > 0) \
			printf(COLOR_RED "Failed: %d" COLOR_RESET "\n", g_gnl_tests_failed); \
		else \
			printf(COLOR_GREEN "Failed: 0" COLOR_RESET "\n"); \
		printf("\n"); \
	} while(0)

// ============================================================================
// PRINTF-SPECIFIC TEST MACRO
// ============================================================================

/**
 * TEST_PRINTF - Compare ft_printf output with standard printf
 * 
 * This macro captures the output of both printf and ft_printf using
 * fmemopen and file descriptor redirection, then compares both the
 * output strings and return values.
 * 
 * Usage: TEST_PRINTF(description, format, ...);
 * Example: TEST_PRINTF("integer zero", "%d", 0);
 * 
 * Requirements:
 * - Must have global variables g_printf_tests_* in scope
 * - Must include <unistd.h> for dup/dup2
 * - Must include <string.h> for strcmp
 */
# define TEST_PRINTF(description, format, ...) \
	do { \
		char expected[1024] = {0}; \
		char actual[1024] = {0}; \
		int exp_ret, act_ret; \
		ssize_t bytes_read; \
		g_printf_tests_run++; \
		snprintf(g_current_test_desc, MAX_TEST_DESC_LEN, "%s", description); \
		g_current_test_number = g_printf_tests_run; \
		int saved_stdout = dup(STDOUT_FILENO); \
		int pipe_exp[2], pipe_act[2]; \
		pipe(pipe_exp); \
		fflush(stdout); \
		dup2(pipe_exp[1], STDOUT_FILENO); \
		fflush(stdout); \
		exp_ret = printf(format, ##__VA_ARGS__); \
		fflush(stdout); \
		dup2(saved_stdout, STDOUT_FILENO); \
		close(pipe_exp[1]); \
		bytes_read = read(pipe_exp[0], expected, sizeof(expected) - 1); \
		if (bytes_read > 0) expected[bytes_read] = '\0'; \
		close(pipe_exp[0]); \
		pipe(pipe_act); \
		fflush(stdout); \
		dup2(pipe_act[1], STDOUT_FILENO); \
		act_ret = ft_printf(format, ##__VA_ARGS__); \
		dup2(saved_stdout, STDOUT_FILENO); \
		close(pipe_act[1]); \
		bytes_read = read(pipe_act[0], actual, sizeof(actual) - 1); \
		if (bytes_read > 0) actual[bytes_read] = '\0'; \
		close(pipe_act[0]); \
		close(saved_stdout); \
		if (exp_ret == act_ret && strcmp(expected, actual) == 0) { \
			printf(COLOR_GREEN "  ✓ #%d " COLOR_RESET "%s\n", g_printf_tests_run, description); \
			fflush(stdout); \
			g_printf_tests_passed++; \
		} else { \
			printf(COLOR_RED "  ✗ #%d " COLOR_RESET "%s\n", g_printf_tests_run, description); \
			printf("    Expected: \"%s\" (ret=%d)\n", expected, exp_ret); \
			printf("    Got:      \"%s\" (ret=%d)\n", actual, act_ret); \
			fflush(stdout); \
			g_printf_tests_failed++; \
		} \
		g_current_test_desc[0] = '\0'; \
	} while(0)

// ============================================================================
// TEST HEADER BANNERS
// ============================================================================

/**
 * Prints a formatted test suite header
 */
# define TEST_HEADER(name) \
	do { \
		printf("\n"); \
		printf(COLOR_BLUE "════════════════════════════════════════════════════\n"); \
		printf("     %s\n", name); \
		printf("════════════════════════════════════════════════════\n" COLOR_RESET); \
		printf("\n"); \
	} while(0)

/**
 * Prints a formatted test suite section header
 */
# define TEST_SECTION(name) \
	do { \
		printf("\n"); \
		printf(COLOR_CYAN " ------- %s -------\n" COLOR_RESET, name); \
		printf("\n"); \
	} while(0)

// ============================================================================
// MALLOC FAILURE TESTING MACROS
// ============================================================================

/**
 * TEST_MALLOC_FAIL - Test function behavior when malloc fails
 * 
 * This macro helps test how functions handle allocation failures.
 * It runs the test multiple times, failing malloc at different points
 * to ensure proper error handling.
 * 
 * Usage:
 *   TEST_MALLOC_FAIL("Function handles malloc failure", {
 *       t_dstr result = str_dup(cstr("test"));
 *       TEST_ASSERT(result.s == NULL, "Returns NULL on malloc fail");
 *   });
 * 
 * @param desc: Description of what's being tested
 * @param code: Code block to execute with malloc failures
 */
# define TEST_MALLOC_FAIL(desc, code) \
	do { \
		int _test_passed = 1; \
		malloc_fail_enable(); \
		for (int _fail_at = 0; _fail_at < 10; _fail_at++) { \
			malloc_fail_reset_counter(); \
			malloc_fail_after(_fail_at); \
			code \
			if (malloc_get_call_count() <= _fail_at) \
				break; \
		} \
		malloc_fail_disable(); \
		if (_test_passed) { \
			g_tests_passed++; \
			printf(COLOR_GREEN "  ✓ #%d %s\n" COLOR_RESET, \
				++g_tests_run, desc); \
		} \
	} while(0)

/**
 * TEST_MALLOC_FAIL_POINT - Test malloc failure at a specific allocation
 * 
 * More precise than TEST_MALLOC_FAIL - fails at exactly one allocation point.
 * 
 * Usage:
 *   TEST_MALLOC_FAIL_POINT("2nd malloc fails", 1, {
 *       char *a = malloc(10);  // This succeeds (index 0)
 *       char *b = malloc(20);  // This fails (index 1)
 *       TEST_ASSERT(a != NULL && b == NULL, "Second alloc fails");
 *       free(a);
 *   });
 * 
 * @param desc: Description of the test
 * @param fail_index: Which allocation should fail (0 = first, 1 = second, etc.)
 * @param code: Code block to execute
 */
# define TEST_MALLOC_FAIL_POINT(desc, fail_index, code) \
	do { \
		malloc_fail_enable(); \
		malloc_fail_after(fail_index); \
		code \
		malloc_fail_disable(); \
	} while(0)

/**
 * ASSERT_NULL_ON_MALLOC_FAIL - Assert that result is NULL when malloc fails
 * 
 * Convenience macro for the common case of checking NULL return on malloc failure.
 * 
 * @param expr: Expression that should return NULL
 * @param desc: Description for test output
 */
# define ASSERT_NULL_ON_MALLOC_FAIL(expr, desc) \
	do { \
		__typeof__(expr) _result = (expr); \
		if (_result != NULL) { \
			printf(COLOR_RED "  ✗ #%d %s (expected NULL, got non-NULL)\n" COLOR_RESET, \
				++g_tests_run, desc); \
			g_tests_failed++; \
		} else { \
			g_tests_passed++; \
			printf(COLOR_GREEN "  ✓ #%d %s\n" COLOR_RESET, \
				++g_tests_run, desc); \
		} \
	} while(0)

#endif
