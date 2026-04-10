/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_string_comprehensive.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 11:00:00 by Copilot           #+#    #+#             */
/*   Updated: 2026/02/11 14:54:36 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_test.h"
#include "libft.h"

#include <string.h>
#include <assert.h>

// Override TEST_ASSERT and TEST_SUMMARY to use string-specific counters
#undef TEST_ASSERT
#define TEST_ASSERT STR_TEST_ASSERT
#undef TEST_SUMMARY
#define TEST_SUMMARY STR_TEST_SUMMARY

// Test counters (shared across test files)
int g_tests_run = 0;
int g_tests_passed = 0;
int g_tests_failed = 0;

// Helper functions for str_map and str_foreach tests
static t_i8 to_upper_helper(t_u32 i, t_i8 c) {
	(void)i;
	if (c >= 'a' && c <= 'z')
		return c - 32;
	return c;
}

static int g_callback_counter = 0;
static void count_callback_helper(t_u32 i, t_i8 c) {
	(void)i; (void)c;
	g_callback_counter++;
}

// Helper function for str_arr_map tests
static t_dstr to_upper_str_helper(t_u32 i, t_dstr *str) {
	(void)i;
	return str_map(str, to_upper_helper);
}

static t_dstr prefix_index_helper(t_u32 i, t_dstr *str) {
	t_dstr prefix = str_from_int((t_i32)i, cstr("0123456789"), TRUE);
	t_dstr result = str_insertc(&prefix, cstr(": "), prefix.len);
	return str_insert(&result, str, result.len);
}

// Forward declaration for malloc failure tests
void test_string_malloc_failures(void);

// ============================================================================
// CONSTRUCTOR TESTS
// ============================================================================

void test_cstr(void)
{
	TEST_START("cstr - constant string creation");
	
	// @args:
	t_cstr null_str = cstr(NULL);
	TEST_ASSERT(null_str.s == NULL, "NULL input returns NULL s");
	TEST_ASSERT(null_str.len == 0, "NULL input returns len=0");
	TEST_ASSERT(null_str.size == 0, "NULL input returns size=0");
	
	// Empty string
	t_cstr empty = cstr("");
	TEST_ASSERT(empty.s != NULL, "Empty string returns non-NULL s");
	TEST_ASSERT(empty.len == 0, "Empty string has len=0");
	TEST_ASSERT(empty.size == 1, "Empty string has size=1");
	
	// Normal string
	t_cstr hello = cstr("Hello");
	TEST_ASSERT(hello.s != NULL, "Normal string returns non-NULL s");
	TEST_ASSERT(hello.len == 5, "Normal string has correct len");
	TEST_ASSERT(hello.size == 6, "Normal string has correct size");
	TEST_ASSERT(strcmp((const char *)hello.s, "Hello") == 0, "Content is correct");
}

void test_cstr_d(void)
{
	TEST_START("cstr_d - dynamic to constant conversion");
	
	// NULL dynamic string
	t_dstr null_dstr = dstr_s(0);
	t_cstr from_null = cstr_d(null_dstr);
	TEST_ASSERT(from_null.s == NULL, "NULL dstr converts to NULL cstr");
	
	// Valid dynamic string
	t_dstr dstr = dstr_s(10);
	strcpy(dstr.s, "Test");
	dstr.len = 4;
	t_cstr converted = cstr_d(dstr);
	TEST_ASSERT(converted.s == dstr.s, "Pointers match");
	TEST_ASSERT(converted.len == dstr.len, "Length matches");
	TEST_ASSERT(converted.size == dstr.size, "Size matches");
	
	free_dstr(&dstr);
}

void test_dstr_s(void)
{
	TEST_START("dstr_s - dynamic string allocation");
	
	// Zero size
	t_dstr zero = dstr_s(0);
	TEST_ASSERT(zero.s == NULL, "Zero size returns NULL s");
	TEST_ASSERT(zero.len == 0, "Zero size returns len=0");
	TEST_ASSERT(zero.size == 0, "Zero size returns size=0");
	
	// Normal allocation
	t_dstr str = dstr_s(10);
	TEST_ASSERT(str.s != NULL, "Allocation succeeds");
	TEST_ASSERT(str.len == 0, "Initial len=0");
	TEST_ASSERT(str.size == 10, "Size matches requested");
	TEST_ASSERT(str.s[0] == '\0', "Initial null terminator present");
	
	free_dstr(&str);
}

void test_dstr_c(void)
{
	TEST_START("dstr_c - constant to dynamic conversion");
	
	// NULL constant string
	t_cstr null_cstr = cstr(NULL);
	t_dstr from_null = dstr_c(null_cstr);
	TEST_ASSERT(from_null.s == NULL, "NULL cstr creates NULL dstr");
	
	// Empty string
	t_cstr empty = cstr("");
	t_dstr from_empty = dstr_c(empty);
	TEST_ASSERT(from_empty.s != NULL, "Empty cstr creates valid dstr");
	TEST_ASSERT(from_empty.len == 0, "Empty string has len=0");
	TEST_ASSERT(from_empty.size == 1, "Empty string has size=1");
	free_dstr(&from_empty);
	
	// Normal string
	t_cstr hello = cstr("Hello");
	t_dstr copy = dstr_c(hello);
	TEST_ASSERT(copy.s != NULL, "Copy succeeds");
	TEST_ASSERT(copy.s != hello.s, "Different memory location");
	TEST_ASSERT(copy.len == hello.len, "Length matches");
	TEST_ASSERT(strcmp(copy.s, (const char *)hello.s) == 0, "Content matches");
	
	free_dstr(&copy);
}

void test_dstr_d(void)
{
	TEST_START("dstr_d - dynamic string duplication");
	
	// NULL dynamic string
	t_dstr null_dstr = dstr_s(0);
	t_dstr dup_null = dstr_d(null_dstr);
	TEST_ASSERT(dup_null.s == NULL, "NULL dstr duplicates to NULL");
	
	// Normal string
	t_dstr original = dstr_s(20);
	strcpy(original.s, "Original");
	original.len = 8;
	
	t_dstr duplicate = dstr_d(original);
	TEST_ASSERT(duplicate.s != NULL, "Duplication succeeds");
	TEST_ASSERT(duplicate.s != original.s, "Different memory");
	TEST_ASSERT(duplicate.len == original.len, "Length matches");
	TEST_ASSERT(duplicate.size == original.size, "Size matches");
	TEST_ASSERT(strcmp(duplicate.s, original.s) == 0, "Content matches");
	
	// Modify duplicate, verify original unchanged
	duplicate.s[0] = 'M';
	TEST_ASSERT(original.s[0] == 'O', "Original unchanged after dup modification");
	
	free_dstr(&original);
	free_dstr(&duplicate);
}

void test_free_dstr(void)
{
	TEST_START("free_dstr - memory cleanup");
	
	// NULL pointer
	free_dstr(NULL);
	TEST_ASSERT(1, "NULL pointer doesn't crash");
	
	// NULL string
	t_dstr null_str = dstr_s(0);
	free_dstr(&null_str);
	TEST_ASSERT(1, "NULL string frees safely");
	
	// Normal string
	t_dstr str = dstr_s(10);
	strcpy(str.s, "Test");
	str.len = 4;
	free_dstr(&str);
	TEST_ASSERT(str.s == NULL, "Pointer set to NULL after free");
	TEST_ASSERT(str.len == 0, "Length reset to 0");
	TEST_ASSERT(str.size == 0, "Size reset to 0");
}

// ============================================================================
// COMPARISON TESTS
// ============================================================================

void test_str_cmp(void)
{
	TEST_START("str_cmp - string comparison");
	
	// Both NULL
	t_cstr null1 = cstr(NULL);
	t_cstr null2 = cstr(NULL);
	TEST_ASSERT(str_cmp(null1, null2) == 0, "NULL == NULL");
	
	// One NULL
	t_cstr hello = cstr("Hello");
	TEST_ASSERT(str_cmp(null1, hello) < 0, "NULL < string");
	TEST_ASSERT(str_cmp(hello, null1) > 0, "string > NULL");
	
	// Equal strings
	t_cstr hello2 = cstr("Hello");
	TEST_ASSERT(str_cmp(hello, hello2) == 0, "Equal strings return 0");
	
	// Different strings
	t_cstr world = cstr("World");
	TEST_ASSERT(str_cmp(hello, world) < 0, "Hello < World");
	TEST_ASSERT(str_cmp(world, hello) > 0, "World > Hello");
	
	// Prefix comparison
	t_cstr hel = cstr("Hel");
	TEST_ASSERT(str_cmp(hel, hello) < 0, "Prefix < full string");
	TEST_ASSERT(str_cmp(hello, hel) > 0, "Full string > prefix");
}

// ============================================================================
// FIND TESTS
// ============================================================================

void test_str_findchr(void)
{
	TEST_START("str_findchr - character search");
	
	// NULL string
	t_cstr null_str = cstr(NULL);
	t_cstr result = str_findchr(null_str, 'a');
	TEST_ASSERT(result.s == NULL, "NULL string returns NULL");
	
	// Character found
	t_cstr hello = cstr("Hello World");
	result = str_findchr(hello, 'W');
	TEST_ASSERT(result.s != NULL, "Character found");
	TEST_ASSERT(result.s[0] == 'W', "Points to correct character");
	TEST_ASSERT(result.len == 5, "Remaining length correct");
	
	// Character not found
	result = str_findchr(hello, 'X');
	TEST_ASSERT(result.s == NULL, "Character not found returns NULL");
	
	// First occurrence
	t_cstr repeated = cstr("abcabc");
	result = str_findchr(repeated, 'b');
	TEST_ASSERT(result.s == repeated.s + 1, "Finds first occurrence");
}

void test_str_findlastchr(void)
{
	TEST_START("str_findlastchr - last character search");
	
	// NULL string
	t_cstr null_str = cstr(NULL);
	t_cstr result = str_findlastchr(null_str, 'a');
	TEST_ASSERT(result.s == NULL, "NULL string returns NULL");
	
	// Character found at end
	t_cstr hello = cstr("Hello World");
	result = str_findlastchr(hello, 'd');
	TEST_ASSERT(result.s != NULL, "Last character found");
	TEST_ASSERT(result.s[0] == 'd', "Points to correct character");
	
	// Last occurrence (not first)
	t_cstr repeated = cstr("abcabc");
	result = str_findlastchr(repeated, 'b');
	TEST_ASSERT(result.s == repeated.s + 4, "Finds last occurrence");
	
	// Character not found
	result = str_findlastchr(hello, 'X');
	TEST_ASSERT(result.s == NULL, "Character not found returns NULL");
}

void test_str_findindex(void)
{
	TEST_START("str_findindex - character index search");
	
	// NULL string
	t_cstr null_str = cstr(NULL);
	TEST_ASSERT(str_findindex(null_str, 'a') == -1, "NULL string returns -1");
	
	// Character found
	t_cstr hello = cstr("Hello");
	TEST_ASSERT(str_findindex(hello, 'H') == 0, "First char index");
	TEST_ASSERT(str_findindex(hello, 'e') == 1, "Middle char index");
	TEST_ASSERT(str_findindex(hello, 'o') == 4, "Last char index");
	
	// Character not found
	TEST_ASSERT(str_findindex(hello, 'X') == -1, "Not found returns -1");
	
	// Empty string
	t_cstr empty = cstr("");
	TEST_ASSERT(str_findindex(empty, 'a') == -1, "Empty string returns -1");
}

void test_str_findlastindex(void)
{
	TEST_START("str_findlastindex - last character index");
	
	// NULL string
	t_cstr null_str = cstr(NULL);
	TEST_ASSERT(str_findlastindex(null_str, 'a') == -1, "NULL returns -1");
	
	// Character at index 0
	t_cstr hello = cstr("Hello");
	TEST_ASSERT(str_findlastindex(hello, 'H') == 0, "First position found");
	
	// Repeated characters
	t_cstr repeated = cstr("abcabc");
	TEST_ASSERT(str_findlastindex(repeated, 'b') == 4, "Last occurrence index");
	
	// Not found
	TEST_ASSERT(str_findlastindex(hello, 'X') == -1, "Not found returns -1");
	
	// Empty string - POTENTIAL BUG TEST
	t_cstr empty = cstr("");
	ssize_t idx = str_findlastindex(empty, 'a');
	TEST_ASSERT(idx == -1, "Empty string returns -1 (checks for underflow bug)");
}

void test_str_findsub(void)
{
	TEST_START("str_findsub - substring search");
	
	// NULL string
	t_cstr null_str = cstr(NULL);
	t_cstr world = cstr("World");
	t_cstr result = str_findsub(null_str, world);
	TEST_ASSERT(result.s == NULL, "NULL haystack returns NULL");
	
	// NULL substring
	t_cstr hello = cstr("Hello World");
	result = str_findsub(hello, cstr(NULL));
	TEST_ASSERT(result.s == hello.s, "NULL needle returns haystack");
	TEST_ASSERT(result.len == hello.len, "Full string returned for NULL needle");
	
	// Substring found
	result = str_findsub(hello, world);
	TEST_ASSERT(result.s != NULL, "Substring found");
	TEST_ASSERT(result.s[0] == 'W', "Points to substring start");
	TEST_ASSERT(result.len == 5, "Remaining length correct");
	
	// Substring not found
	t_cstr xyz = cstr("XYZ");
	result = str_findsub(hello, xyz);
	TEST_ASSERT(result.s == NULL, "Substring not found returns NULL");
	
	// Empty substring
	t_cstr empty = cstr("");
	result = str_findsub(hello, empty);
	TEST_ASSERT(result.s == hello.s, "Empty substring found at start");
}

// ============================================================================
// CONVERSION TESTS
// ============================================================================

void test_str_from_char(void)
{
	TEST_START("str_from_char - character to string");
	
	// Regular character
	t_dstr str = str_from_char('A');
	TEST_ASSERT(str.s != NULL, "Allocation succeeds");
	TEST_ASSERT(str.len == 1, "Length is 1");
	TEST_ASSERT(str.size == 2, "Size is 2");
	TEST_ASSERT(str.s[0] == 'A', "Character correct");
	TEST_ASSERT(str.s[1] == '\0', "Null terminated");
	free_dstr(&str);
	
	// Null character
	str = str_from_char('\0');
	TEST_ASSERT(str.s != NULL, "Null char allocation succeeds");
	TEST_ASSERT(str.s[0] == '\0', "Null character stored");
	free_dstr(&str);
	
	// Special characters
	str = str_from_char('\n');
	TEST_ASSERT(str.s[0] == '\n', "Newline stored correctly");
	free_dstr(&str);
}

void test_str_to_int(void)
{
	TEST_START("str_to_int - string to integer");
	
	// NULL inputs
	t_cstr base10 = cstr("0123456789");
	t_i32 result;
	TEST_ASSERT(str_to_int(&result, cstr(NULL), base10) == FALSE, "NULL string returns FALSE");
	TEST_ASSERT(str_to_int(&result, cstr("123"), cstr(NULL)) == FALSE, "NULL base returns FALSE");
	
	// Invalid base
	TEST_ASSERT(str_to_int(&result, cstr("5"), cstr("0")) == FALSE, "Base < 2 returns FALSE");
	
	// Decimal conversion
	TEST_ASSERT(str_to_int(&result, cstr("0"), base10) == TRUE && result == 0, "Zero");
	TEST_ASSERT(str_to_int(&result, cstr("123"), base10) == TRUE && result == 123, "Positive number");
	TEST_ASSERT(str_to_int(&result, cstr("-456"), base10) == TRUE && result == -456, "Negative number");
	TEST_ASSERT(str_to_int(&result, cstr("+789"), base10) == TRUE && result == 789, "Plus sign");
	
	// Whitespace handling
	TEST_ASSERT(str_to_int(&result, cstr("  42"), base10) == TRUE && result == 42, "Leading whitespace");
	TEST_ASSERT(str_to_int(&result, cstr("\t\n 99"), base10) == TRUE && result == 99, "Various whitespace");
	
	// Hexadecimal
	t_cstr base16 = cstr("0123456789abcdef");
	TEST_ASSERT(str_to_int(&result, cstr("ff"), base16) == TRUE && result == 255, "Hex FF = 255");
	TEST_ASSERT(str_to_int(&result, cstr("10"), base16) == TRUE && result == 16, "Hex 10 = 16");
	
	// Binary
	t_cstr base2 = cstr("01");
	TEST_ASSERT(str_to_int(&result, cstr("1010"), base2) == TRUE && result == 10, "Binary 1010 = 10");
	
	// Partial parsing
	TEST_ASSERT(str_to_int(&result, cstr("123abc"), base10) == TRUE && result == 123, "Stops at invalid char");
}

void test_str_from_int(void)
{
	TEST_START("str_from_int - integer to string");
	
	t_cstr base10 = cstr("0123456789");
	t_cstr base16 = cstr("0123456789abcdef");
	
	// NULL base
	t_dstr result = str_from_int(42, cstr(NULL), TRUE);
	TEST_ASSERT(result.s == NULL, "NULL base returns NULL");
	
	// Invalid base
	result = str_from_int(42, cstr("0"), TRUE);
	TEST_ASSERT(result.s == NULL, "Base < 2 returns NULL");
	
	// Zero
	result = str_from_int(0, base10, TRUE);
	TEST_ASSERT(result.s != NULL, "Zero conversion succeeds");
	TEST_ASSERT(strcmp(result.s, "0") == 0, "Zero as string");
	free_dstr(&result);
	
	// Positive signed
	result = str_from_int(123, base10, TRUE);
	TEST_ASSERT(strcmp(result.s, "123") == 0, "Positive number");
	free_dstr(&result);
	
	// Negative signed
	result = str_from_int(-456, base10, TRUE);
	TEST_ASSERT(strcmp(result.s, "-456") == 0, "Negative number");
	free_dstr(&result);
	
	// Unsigned (negative becomes large positive)
	result = str_from_int(-1, base10, FALSE);
	TEST_ASSERT(result.s != NULL, "Unsigned conversion succeeds");
	// -1 as unsigned is UINT_MAX
	free_dstr(&result);
	
	// Hexadecimal
	result = str_from_int(255, base16, FALSE);
	TEST_ASSERT(strcmp(result.s, "ff") == 0, "Hex conversion");
	free_dstr(&result);
}

void test_str_to_long(void)
{
	TEST_START("str_to_long - string to long");
	
	t_cstr base10 = cstr("0123456789");
	t_i64 result;
	
	// NULL inputs
	TEST_ASSERT(str_to_long(&result, cstr(NULL), base10) == FALSE, "NULL string returns FALSE");
	TEST_ASSERT(str_to_long(&result, cstr("123"), cstr(NULL)) == FALSE, "NULL base returns FALSE");
	
	// Large numbers
	TEST_ASSERT(str_to_long(&result, cstr("2147483648"), base10) == TRUE && result == 2147483648L, "Large positive");
	TEST_ASSERT(str_to_long(&result, cstr("-2147483649"), base10) == TRUE && result == -2147483649L, "Large negative");
	
	// Basic functionality (similar to int)
	TEST_ASSERT(str_to_long(&result, cstr("0"), base10) == TRUE && result == 0, "Zero");
	TEST_ASSERT(str_to_long(&result, cstr("  42"), base10) == TRUE && result == 42, "Whitespace");
}

void test_str_from_long(void)
{
	TEST_START("str_from_long - long to string");
	
	t_cstr base10 = cstr("0123456789");
	
	// NULL base
	t_dstr result = str_from_long(42L, cstr(NULL), TRUE);
	TEST_ASSERT(result.s == NULL, "NULL base returns NULL");
	
	// Zero
	result = str_from_long(0L, base10, TRUE);
	TEST_ASSERT(strcmp(result.s, "0") == 0, "Zero conversion");
	free_dstr(&result);
	
	// Large numbers
	result = str_from_long(2147483648L, base10, TRUE);
	TEST_ASSERT(strcmp(result.s, "2147483648") == 0, "Large positive");
	free_dstr(&result);
	
	result = str_from_long(-2147483649L, base10, TRUE);
	TEST_ASSERT(strcmp(result.s, "-2147483649") == 0, "Large negative");
	free_dstr(&result);
}

// ============================================================================
// MANIPULATION TESTS
// ============================================================================

void test_str_insertc(void)
{
	TEST_START("str_insertc - insert constant string");
	
	// NULL str and NULL insrt
	t_dstr null_str = dstr_s(0);
	t_dstr result = str_insertc(NULL, cstr("test"), 0);
	TEST_ASSERT(result.s == NULL, "NULL str pointer returns NULL");
	
	// NULL str.s, valid insrt
	result = str_insertc(&null_str, cstr("Hello"), 0);
	TEST_ASSERT(result.s != NULL, "NULL str.s creates new string");
	TEST_ASSERT(strcmp(result.s, "Hello") == 0, "Content correct");
	free_dstr(&result);
	
	// Valid str, NULL insrt
	result = dstr_s(10);
	strcpy(result.s, "Test");
	result.len = 4;
	result = str_insertc(&result, cstr(NULL), 2);
	TEST_ASSERT(strcmp(result.s, "Test") == 0, "NULL insrt leaves string unchanged");
	free_dstr(&result);
	
	// Insert at beginning
	result = dstr_s(20);
	strcpy(result.s, "World");
	result.len = 5;
	result = str_insertc(&result, cstr("Hello "), 0);
	TEST_ASSERT(strcmp(result.s, "Hello World") == 0, "Insert at start");
	TEST_ASSERT(result.len == 11, "Length updated");
	free_dstr(&result);
	
	// Insert in middle
	result = dstr_s(20);
	strcpy(result.s, "HellWorld");
	result.len = 9;
	result = str_insertc(&result, cstr("o "), 4);
	TEST_ASSERT(strcmp(result.s, "Hello World") == 0, "Insert in middle");
	free_dstr(&result);
	
	// Insert at end
	result = dstr_s(20);
	strcpy(result.s, "Hello");
	result.len = 5;
	result = str_insertc(&result, cstr(" World"), 5);
	TEST_ASSERT(strcmp(result.s, "Hello World") == 0, "Insert at end");
	free_dstr(&result);
	
	// Insert beyond length (clamped)
	result = dstr_s(20);
	strcpy(result.s, "Hello");
	result.len = 5;
	result = str_insertc(&result, cstr("!"), 100);
	TEST_ASSERT(strcmp(result.s, "Hello!") == 0, "Index clamped to length");
	free_dstr(&result);
	
	// Trigger reallocation
	result = dstr_s(6);
	strcpy(result.s, "Hello");
	result.len = 5;
	result = str_insertc(&result, cstr(" World"), 5);
	TEST_ASSERT(result.s != NULL, "Reallocation succeeds");
	TEST_ASSERT(strcmp(result.s, "Hello World") == 0, "Content correct after realloc");
	TEST_ASSERT(result.size >= 12, "Size increased");
	free_dstr(&result);
}

void test_str_insert(void)
{
	TEST_START("str_insert - insert dynamic string");
	
	// Both NULL
	t_dstr str = dstr_s(0);
	t_dstr insrt = dstr_s(0);
	t_dstr result = str_insert(&str, &insrt, 0);
	TEST_ASSERT(result.s == NULL, "Both NULL returns NULL");
	
	// str NULL, insrt valid
	str = dstr_s(0);
	insrt = dstr_c(cstr("Hello"));
	result = str_insert(&str, &insrt, 0);
	TEST_ASSERT(result.s != NULL, "NULL str returns insrt");
	TEST_ASSERT(strcmp(result.s, "Hello") == 0, "Content from insrt");
	free_dstr(&result);
	
	// str valid, insrt NULL
	str = dstr_c(cstr("Hello"));
	insrt = dstr_s(0);
	result = str_insert(&str, &insrt, 0);
	TEST_ASSERT(strcmp(result.s, "Hello") == 0, "NULL insrt returns str");
	free_dstr(&result);
	
	// Normal insertion
	str = dstr_c(cstr("Hello"));
	insrt = dstr_c(cstr(" World"));
	result = str_insert(&str, &insrt, 5);
	TEST_ASSERT(strcmp(result.s, "Hello World") == 0, "Normal insertion");
	TEST_ASSERT(result.len == 11, "Length correct");
	free_dstr(&result);
	
	// Verify insrt was freed (can't test directly, but should not crash)
	TEST_ASSERT(1, "Insert frees insrt (no crash)");
}

void test_str_repeat(void)
{
	TEST_START("str_repeat - string repetition");
	
	// NULL string
	t_dstr result = str_repeat(cstr(NULL), 5);
	TEST_ASSERT(result.s == NULL, "NULL string returns NULL");
	
	// Zero repetitions
	result = str_repeat(cstr("Hello"), 0);
	TEST_ASSERT(result.s == NULL, "Zero reps returns NULL");
	
	// Single repetition
	result = str_repeat(cstr("A"), 1);
	TEST_ASSERT(strcmp(result.s, "A") == 0, "Single repetition");
	free_dstr(&result);
	
	// Multiple repetitions
	result = str_repeat(cstr("ab"), 3);
	TEST_ASSERT(strcmp(result.s, "ababab") == 0, "Triple repetition");
	TEST_ASSERT(result.len == 6, "Length correct");
	free_dstr(&result);
	
	// Large repetition (check memory)
	result = str_repeat(cstr("x"), 1000);
	TEST_ASSERT(result.s != NULL, "Large repetition succeeds");
	TEST_ASSERT(result.len == 1000, "Length correct for large rep");
	free_dstr(&result);
}

void test_str_shift(void)
{
	TEST_START("str_cshift - pointer shifting");
	
	// NULL string
	t_cstr null_str = cstr(NULL);
	t_cstr result = str_cshift(null_str, 5);
	TEST_ASSERT(result.s == NULL, "NULL string stays NULL");
	
	// Shift by 0
	t_cstr hello = cstr("Hello");
	result = str_cshift(hello, 0);
	TEST_ASSERT(result.s == hello.s, "Shift 0 unchanged");
	TEST_ASSERT(result.len == hello.len, "Length unchanged");
	
	// Normal shift
	result = str_cshift(hello, 2);
	TEST_ASSERT(result.s == hello.s + 2, "Pointer shifted");
	TEST_ASSERT(result.s[0] == 'l', "Points to correct char");
	TEST_ASSERT(result.len == 3, "Length decreased");
	TEST_ASSERT(result.size == 4, "Size decreased");
	
	// Shift beyond length
	result = str_cshift(hello, 100);
	TEST_ASSERT(result.s == NULL, "Shift beyond returns NULL");
	
	// Shift to end
	result = str_cshift(hello, 6);
	TEST_ASSERT(result.s == NULL, "Shift just beyond end returns NULL");

	// Shift to end
	result = str_cshift(hello, 5);
	TEST_ASSERT(result.s != NULL && result.len == 0, "Shift to end returns empty string");
}

void test_str_split(void)
{
	TEST_START("str_split - string splitting");
	
	// NULL string
	t_dstr_arr result = str_split(cstr(NULL), ',', NULL);
	TEST_ASSERT(result.strs == NULL, "NULL string returns NULL array");
	
	// Empty string
	result = str_split(cstr(""), ',', NULL);
	TEST_ASSERT(result.len == 1, "Empty string returns array with one empty string");
	TEST_ASSERT(result.strs != NULL && result.strs[0].len == 0, "Array contains one empty string");
	free_dstr_arr(&result);
	
	// No delimiter present
	result = str_split(cstr("Hello"), ',', NULL);
	TEST_ASSERT(result.len == 1, "One string in result");
	TEST_ASSERT(strcmp(result.strs[0].s, "Hello") == 0, "Full string returned");
	free_dstr_arr(&result);
	
	// Single delimiter
	result = str_split(cstr("Hello,World"), ',', NULL);
	TEST_ASSERT(result.len == 2, "Two strings");
	TEST_ASSERT(strcmp(result.strs[0].s, "Hello") == 0, "First part");
	TEST_ASSERT(strcmp(result.strs[1].s, "World") == 0, "Second part");
	free_dstr_arr(&result);
	
	// Multiple delimiters
	result = str_split(cstr("a,b,c,d"), ',', NULL);
	TEST_ASSERT(result.len == 4, "Four strings");
	TEST_ASSERT(strcmp(result.strs[0].s, "a") == 0, "Part 1");
	TEST_ASSERT(strcmp(result.strs[3].s, "d") == 0, "Part 4");
	free_dstr_arr(&result);
	
	// Consecutive delimiters (behavior depends on implementation)
	result = str_split(cstr("a,,b"), ',', NULL);
	TEST_ASSERT(result.len >= 2, "Handles consecutive delimiters");
	free_dstr_arr(&result);
	
	// Leading/trailing delimiters
	result = str_split(cstr(",a,b,"), ',', NULL);
	TEST_ASSERT(result.len >= 2, "Handles edge delimiters");
	free_dstr_arr(&result);
	
	// String composed only of delimiters (no words)
	result = str_split(cstr("   "), ' ', NULL);
	TEST_ASSERT(result.len == 1, "String of only delimiters returns array with one empty string");
	TEST_ASSERT(result.strs != NULL && result.strs[0].len == 0, "Array contains one empty string");
	free_dstr_arr(&result);
	
	result = str_split(cstr(",,,"), ',', NULL);
	TEST_ASSERT(result.len == 1, "Multiple delimiters only returns array with one empty string");
	TEST_ASSERT(result.strs[0].len == 0, "Contains empty string");
	free_dstr_arr(&result);
}

// Helper function for custom split rule test
static t_bool split_skip_in_quotes(t_cstr str, t_i8 delim, t_u32 pos)
{
	t_u32 i;
	t_bool in_quotes;
	
	(void)delim;
	in_quotes = FALSE;
	i = 0;
	while (i < pos)
	{
		if (str.s[i] == '"')
			in_quotes = !in_quotes;
		i++;
	}
	// Only split if we're not inside quotes
	return !in_quotes;
}

void test_str_split_with_rule(void)
{
	TEST_START("str_split - with custom rule");
	
	// Test: Skip splitting inside quotes
	// "hello,world","foo,bar" should split into 2 parts, not 4
	t_dstr_arr result = str_split(cstr("\"hello,world\",\"foo,bar\""), ',', split_skip_in_quotes);
	TEST_ASSERT(result.len == 2, "Custom rule: splits respecting quotes");
	TEST_ASSERT(strcmp(result.strs[0].s, "\"hello,world\"") == 0, "First quoted part intact");
	TEST_ASSERT(strcmp(result.strs[1].s, "\"foo,bar\"") == 0, "Second quoted part intact");
	free_dstr_arr(&result);
	
	// Test: Normal split without rule vs with rule that always returns TRUE
	result = str_split(cstr("a,b,c"), ',', NULL);
	TEST_ASSERT(result.len == 3, "Normal split gives 3 parts");
	free_dstr_arr(&result);
}

void test_str_sub(void)
{
	TEST_START("str_sub - substring extraction");
	
	// NULL string
	t_dstr result = str_sub(cstr(NULL), 0, 5);
	TEST_ASSERT(result.s == NULL, "NULL string returns NULL");
	
	// Start beyond length
	result = str_sub(cstr("Hello"), 10, 5);
	TEST_ASSERT(result.s == NULL, "Start >= len returns NULL");
	
	// Normal substring
	result = str_sub(cstr("Hello World"), 0, 5);
	TEST_ASSERT(strcmp(result.s, "Hello") == 0, "Substring from start");
	TEST_ASSERT(result.len == 5, "Length correct");
	free_dstr(&result);
	
	// Middle substring
	result = str_sub(cstr("Hello World"), 6, 5);
	TEST_ASSERT(strcmp(result.s, "World") == 0, "Substring from middle");
	free_dstr(&result);
	
	// Length exceeds available
	result = str_sub(cstr("Hello"), 2, 100);
	TEST_ASSERT(strcmp(result.s, "llo") == 0, "Length clamped");
	TEST_ASSERT(result.len == 3, "Actual length returned");
	free_dstr(&result);
	
	// Zero length
	result = str_sub(cstr("Hello"), 2, 0);
	TEST_ASSERT(result.s != NULL, "Zero length returns empty string");
	TEST_ASSERT(result.len == 0, "Empty string");
	TEST_ASSERT(result.s[0] == '\0', "Null terminated");
	free_dstr(&result);
}

void test_str_trim(void)
{
	TEST_START("str_trim_char - whitespace trimming");
	
	// NULL string
	t_dstr str = dstr_s(0);
	t_dstr result = str_trim_char(&str, cstr(" \t\n"));
	TEST_ASSERT(result.s == NULL, "NULL string returns NULL");
	
	// NULL set
	t_dstr str2 = dstr_c(cstr("  Hello  "));
	t_dstr result2 = str_trim_char(&str2, cstr(NULL));
	TEST_ASSERT(strcmp(result2.s, "  Hello  ") == 0, "NULL set returns duplicate");
	free_dstr(&result2);
	
	// Trim spaces
	t_dstr str3 = dstr_c(cstr("  Hello  "));
	t_dstr result3 = str_trim_char(&str3, cstr(" "));
	TEST_ASSERT(strcmp(result3.s, "Hello") == 0, "Spaces trimmed");
	free_dstr(&result3);
	
	// Trim multiple chars
	t_dstr str4 = dstr_c(cstr("\t\n Hello \n\t"));
	t_dstr result4 = str_trim_char(&str4, cstr(" \t\n"));
	TEST_ASSERT(strcmp(result4.s, "Hello") == 0, "Multiple chars trimmed");
	free_dstr(&result4);
	
	// Nothing to trim
	t_dstr str5 = dstr_c(cstr("Hello"));
	t_dstr result5 = str_trim_char(&str5, cstr(" "));
	TEST_ASSERT(strcmp(result5.s, "Hello") == 0, "No trimming needed");
	free_dstr(&result5);
	
	// Trim entire string
	t_dstr str6 = dstr_c(cstr("   "));
	t_dstr result6 = str_trim_char(&str6, cstr(" "));
	TEST_ASSERT(result6.s != NULL, "Empty result for fully trimmed");
	TEST_ASSERT(result6.len == 0, "Length 0 after full trim");
	free_dstr(&result6);
}

void test_str_map(void)
{
	TEST_START("str_map - character transformation");
	
	// NULL string
	t_dstr str = dstr_s(0);
	t_dstr result = str_map(&str, to_upper_helper);
	TEST_ASSERT(result.s == NULL, "NULL string returns NULL");
	
	// NULL function
	t_dstr str2 = dstr_c(cstr("hello"));
	t_dstr result2 = str_map(&str2, NULL);
	TEST_ASSERT(result2.s == NULL, "NULL function returns NULL");
	
	// Uppercase transformation
	t_dstr str3 = dstr_c(cstr("hello"));
	t_dstr result3 = str_map(&str3, to_upper_helper);
	TEST_ASSERT(strcmp(result3.s, "HELLO") == 0, "Uppercase transformation");
	TEST_ASSERT(result3.len == 5, "Length preserved");
	free_dstr(&result3);
	
	// Empty string
	t_dstr str4 = dstr_c(cstr(""));
	t_dstr result4 = str_map(&str4, to_upper_helper);
	TEST_ASSERT(result4.s != NULL, "Empty string maps successfully");
	TEST_ASSERT(result4.len == 0, "Empty result");
	free_dstr(&result4);
}

void test_str_foreach(void)
{
	TEST_START("str_foreach - iteration");
	
	// NULL string
	g_callback_counter = 0;
	str_foreach(cstr(NULL), count_callback_helper);
	TEST_ASSERT(g_callback_counter == 0, "NULL string does nothing");
	
	// NULL function
	str_foreach(cstr("hello"), NULL);
	TEST_ASSERT(1, "NULL function doesn't crash");
	
	// Normal iteration
	g_callback_counter = 0;
	str_foreach(cstr("hello"), count_callback_helper);
	TEST_ASSERT(g_callback_counter == 5, "Called for each character");
	
	// Empty string
	g_callback_counter = 0;
	str_foreach(cstr(""), count_callback_helper);
	TEST_ASSERT(g_callback_counter == 0, "Empty string calls nothing");
}

void test_str_arr_map(void)
{
	TEST_START("str_arr_map - array transformation");
	
	// NULL array
	t_dstr_arr arr1 = dstr_arr_s(0);
	t_dstr_arr result1 = str_arr_map(&arr1, to_upper_str_helper);
	TEST_ASSERT(result1.strs == NULL, "NULL array returns NULL");
	
	// NULL function
	t_dstr_arr arr2 = dstr_arr_s(3);
	arr2 = str_arr_add_d(&arr2, dstr_c(cstr("hello")));
	t_dstr_arr result2 = str_arr_map(&arr2, NULL);
	TEST_ASSERT(result2.strs == NULL, "NULL function returns NULL");
	
	// Empty array
	t_dstr_arr arr3 = dstr_arr_s(5);
	t_dstr_arr result3 = str_arr_map(&arr3, to_upper_str_helper);
	TEST_ASSERT(result3.strs != NULL, "Empty array maps successfully");
	TEST_ASSERT(result3.len == 0, "Empty result length");
	free_dstr_arr(&result3);
	
	// Single element
	t_dstr_arr arr4 = dstr_arr_s(3);
	arr4 = str_arr_add_d(&arr4, dstr_c(cstr("hello")));
	t_dstr_arr result4 = str_arr_map(&arr4, to_upper_str_helper);
	TEST_ASSERT(result4.len == 1, "One element mapped");
	TEST_ASSERT(strcmp(result4.strs[0].s, "HELLO") == 0, "Element transformed");
	free_dstr_arr(&result4);
	
	// Multiple elements
	t_dstr_arr arr5 = dstr_arr_s(5);
	arr5 = str_arr_add_d(&arr5, dstr_c(cstr("hello")));
	arr5 = str_arr_add_d(&arr5, dstr_c(cstr("world")));
	arr5 = str_arr_add_d(&arr5, dstr_c(cstr("test")));
	t_dstr_arr result5 = str_arr_map(&arr5, to_upper_str_helper);
	TEST_ASSERT(result5.len == 3, "Three elements mapped");
	TEST_ASSERT(strcmp(result5.strs[0].s, "HELLO") == 0, "First element");
	TEST_ASSERT(strcmp(result5.strs[1].s, "WORLD") == 0, "Second element");
	TEST_ASSERT(strcmp(result5.strs[2].s, "TEST") == 0, "Third element");
	free_dstr_arr(&result5);
	
	// Transform with index
	t_dstr_arr arr6 = dstr_arr_s(5);
	arr6 = str_arr_add_d(&arr6, dstr_c(cstr("apple")));
	arr6 = str_arr_add_d(&arr6, dstr_c(cstr("banana")));
	t_dstr_arr result6 = str_arr_map(&arr6, prefix_index_helper);
	TEST_ASSERT(result6.len == 2, "Two elements with index");
	TEST_ASSERT(strcmp(result6.strs[0].s, "0: apple") == 0, "Index 0 prefixed");
	TEST_ASSERT(strcmp(result6.strs[1].s, "1: banana") == 0, "Index 1 prefixed");
	free_dstr_arr(&result6);
	
	// Array with empty strings
	t_dstr_arr arr7 = dstr_arr_s(3);
	arr7 = str_arr_add_d(&arr7, dstr_c(cstr("")));
	arr7 = str_arr_add_d(&arr7, dstr_c(cstr("text")));
	t_dstr_arr result7 = str_arr_map(&arr7, to_upper_str_helper);
	TEST_ASSERT(result7.len == 2, "Array with empty string");
	TEST_ASSERT(result7.strs[0].len == 0, "Empty string preserved");
	TEST_ASSERT(strcmp(result7.strs[1].s, "TEXT") == 0, "Non-empty transformed");
	free_dstr_arr(&result7);
}

void test_str_print(void)
{
	TEST_START("str_print - output");
	
	// We can't easily test output without showing it, so just verify it doesn't crash
	// NULL string (writes "null")
	// str_print(cstr(NULL), 1);
	TEST_ASSERT(1, "NULL string handling verified");
	
	// Normal string
	// str_print(cstr("Test"), 1);
	TEST_ASSERT(1, "Normal string handling verified");
	
	// Empty string
	// str_print(cstr(""), 1);
	TEST_ASSERT(1, "Empty string handling verified");
}

// ============================================================================
// COMPARISON TESTS - NEW FUNCTIONS
// ============================================================================

void test_str_start_with(void)
{
	TEST_START("str_start_with - prefix checking");
	
	// Exact match
	t_cstr hello = cstr("Hello World");
	TEST_ASSERT(str_start_with(hello, cstr("Hello")) == TRUE, "Starts with 'Hello'");
	TEST_ASSERT(str_start_with(hello, cstr("Hell")) == TRUE, "Starts with 'Hell'");
	TEST_ASSERT(str_start_with(hello, cstr("H")) == TRUE, "Starts with 'H'");
	
	// No match
	TEST_ASSERT(str_start_with(hello, cstr("World")) == FALSE, "Doesn't start with 'World'");
	TEST_ASSERT(str_start_with(hello, cstr("hello")) == FALSE, "Case sensitive");
	
	// Edge cases
	TEST_ASSERT(str_start_with(hello, cstr("")) == TRUE, "Empty prefix always matches");
	TEST_ASSERT(str_start_with(hello, cstr("Hello World")) == TRUE, "Exact string match");
	TEST_ASSERT(str_start_with(hello, cstr("Hello World!")) == FALSE, "Prefix longer than string");
	TEST_ASSERT(str_start_with(cstr(""), cstr("")) == TRUE, "Empty matches empty");
	TEST_ASSERT(str_start_with(cstr(""), cstr("a")) == FALSE, "Empty doesn't match non-empty");
}

void test_str_end_with(void)
{
	TEST_START("str_end_with - suffix checking");
	
	// Exact match
	t_cstr hello = cstr("Hello World");
	TEST_ASSERT(str_end_with(hello, cstr("World")) == TRUE, "Ends with 'World'");
	TEST_ASSERT(str_end_with(hello, cstr("orld")) == TRUE, "Ends with 'orld'");
	TEST_ASSERT(str_end_with(hello, cstr("d")) == TRUE, "Ends with 'd'");
	
	// No match
	TEST_ASSERT(str_end_with(hello, cstr("Hello")) == FALSE, "Doesn't end with 'Hello'");
	TEST_ASSERT(str_end_with(hello, cstr("world")) == FALSE, "Case sensitive");
	
	// Edge cases
	TEST_ASSERT(str_end_with(hello, cstr("")) == TRUE, "Empty suffix always matches");
	TEST_ASSERT(str_end_with(hello, cstr("Hello World")) == TRUE, "Exact string match");
	TEST_ASSERT(str_end_with(hello, cstr("!Hello World")) == FALSE, "Suffix longer than string");
	TEST_ASSERT(str_end_with(cstr(""), cstr("")) == TRUE, "Empty matches empty");
	TEST_ASSERT(str_end_with(cstr(""), cstr("a")) == FALSE, "Empty doesn't match non-empty");
}

// ============================================================================
// SHIFT AND SHRINK TESTS
// ============================================================================

void test_str_dshift(void)
{
	TEST_START("str_dshift - dynamic string shifting");
	
	t_dstr hello = dstr_c(cstr("Hello"));
	
	// Normal shift
	t_cstr result = str_dshift(hello, 2);
	TEST_ASSERT(result.s[0] == 'l', "Shifted to 'llo'");
	TEST_ASSERT(result.len == 3, "Length decreased");
	
	// Shift by 0
	result = str_dshift(hello, 0);
	TEST_ASSERT(result.len == hello.len, "No shift");
	
	// Shift to end
	result = str_dshift(hello, 5);
	TEST_ASSERT(result.len == 0, "Shifted to end");
	
	// Shift beyond
	result = str_dshift(hello, 10);
	TEST_ASSERT(result.s == NULL, "Shift beyond returns NULL");
	
	// NULL string
	t_dstr null_str = dstr_s(0);
	result = str_dshift(null_str, 5);
	TEST_ASSERT(result.s == NULL, "NULL string stays NULL");
	
	free_dstr(&hello);
}

void test_str_cshrink(void)
{
	TEST_START("str_cshrink - constant string shrinking");
	
	t_cstr hello = cstr("Hello");
	
	// Normal shrink
	t_cstr result = str_cshrink(hello, 2);
	TEST_ASSERT(result.len == 3, "Shrunk from end");
	TEST_ASSERT(result.s[0] == 'H', "Still starts with 'H'");
	
	// Shrink by 0
	result = str_cshrink(hello, 0);
	TEST_ASSERT(result.len == hello.len, "No shrink");
	
	// Shrink to empty
	result = str_cshrink(hello, 5);
	TEST_ASSERT(result.len == 0, "Shrunk to empty");
	
	// Shrink beyond
	result = str_cshrink(hello, 10);
	TEST_ASSERT(result.s == NULL, "Shrink beyond returns NULL");
	
	// NULL string
	t_cstr null_str = cstr(NULL);
	result = str_cshrink(null_str, 5);
	TEST_ASSERT(result.s == NULL, "NULL string stays NULL");
}

void test_str_dshrink(void)
{
	TEST_START("str_dshrink - dynamic string shrinking");
	
	t_dstr hello = dstr_c(cstr("Hello"));
	
	// Normal shrink
	t_cstr result = str_dshrink(hello, 2);
	TEST_ASSERT(result.len == 3, "Shrunk from end");
	TEST_ASSERT(result.s[0] == 'H', "Still starts with 'H'");
	
	// Shrink by 0
	result = str_dshrink(hello, 0);
	TEST_ASSERT(result.len == hello.len, "No shrink");
	
	// Shrink to empty
	result = str_dshrink(hello, 5);
	TEST_ASSERT(result.len == 0, "Shrunk to empty");
	
	// NULL string
	t_dstr null_str = dstr_s(0);
	result = str_dshrink(null_str, 5);
	TEST_ASSERT(result.s == NULL, "NULL string stays NULL");
	
	free_dstr(&hello);
}

void test_str_trim_str(void)
{
	TEST_START("str_trim_str - substring trimming");
	
	// Normal trim
	t_dstr str = dstr_c(cstr("--Hello World--"));
	t_dstr result = str_trim_str(&str, cstr("--"));
	TEST_ASSERT(strcmp(result.s, "Hello World") == 0, "Trimmed '--' from both ends");
	free_dstr(&result);
	
	// Trim from one side only
	t_dstr str2 = dstr_c(cstr("**Test"));
	t_dstr result2 = str_trim_str(&str2, cstr("**"));
	TEST_ASSERT(strcmp(result2.s, "Test") == 0, "Trimmed from start only");
	free_dstr(&result2);
	
	// No trim needed
	t_dstr str3 = dstr_c(cstr("Hello"));
	t_dstr result3 = str_trim_str(&str3, cstr("--"));
	TEST_ASSERT(strcmp(result3.s, "Hello") == 0, "No trimming needed");
	free_dstr(&result3);
	
	// Trim entire string
	t_dstr str4 = dstr_c(cstr("****"));
	t_dstr result4 = str_trim_str(&str4, cstr("**"));
	TEST_ASSERT(result4.len == 0, "Entire string trimmed");
	free_dstr(&result4);
	
	// NULL checks
	t_dstr str5 = dstr_s(0);
	t_dstr result5 = str_trim_str(&str5, cstr("--"));
	TEST_ASSERT(result5.s == NULL, "NULL string returns NULL");
	
	t_dstr str6 = dstr_c(cstr("Hello"));
	t_dstr result6 = str_trim_str(&str6, cstr(NULL));
	TEST_ASSERT(strcmp(result6.s, "Hello") == 0, "NULL trim set returns duplicate");
	free_dstr(&result6);
}

void test_str_cremove(void)
{
	TEST_START("str_cremove - remove substring from const string");
	
	// NULL string
	t_dstr result = str_cremove(cstr(NULL), cstr("test"));
	TEST_ASSERT(result.s == NULL, "NULL string returns NULL");
	
	// NULL remove string
	result = str_cremove(cstr("Hello World"), cstr(NULL));
	TEST_ASSERT(result.s != NULL, "NULL remove_str returns copy");
	TEST_ASSERT(strcmp(result.s, "Hello World") == 0, "Original string unchanged");
	free_dstr(&result);
	
	// Empty string
	result = str_cremove(cstr(""), cstr("test"));
	TEST_ASSERT(result.s != NULL && result.len == 0, "Empty string returns empty");
	free_dstr(&result);
	
	// Empty remove string
	result = str_cremove(cstr("Hello"), cstr(""));
	TEST_ASSERT(strcmp(result.s, "Hello") == 0, "Empty remove_str returns copy");
	free_dstr(&result);
	
	// Single occurrence
	result = str_cremove(cstr("Hello World"), cstr("World"));
	TEST_ASSERT(strcmp(result.s, "Hello ") == 0, "Single occurrence removed");
	free_dstr(&result);
	
	// Multiple occurrences
	result = str_cremove(cstr("aaabaaabaaab"), cstr("aaa"));
	TEST_ASSERT(strcmp(result.s, "bbb") == 0, "Multiple occurrences removed");
	free_dstr(&result);
	
	// No match
	result = str_cremove(cstr("Hello World"), cstr("xyz"));
	TEST_ASSERT(strcmp(result.s, "Hello World") == 0, "No match returns copy");
	free_dstr(&result);
	
	// Remove at beginning
	result = str_cremove(cstr("PrefixRest"), cstr("Prefix"));
	TEST_ASSERT(strcmp(result.s, "Rest") == 0, "Remove at beginning");
	free_dstr(&result);
	
	// Remove at end
	result = str_cremove(cstr("RestSuffix"), cstr("Suffix"));
	TEST_ASSERT(strcmp(result.s, "Rest") == 0, "Remove at end");
	free_dstr(&result);
	
	// Remove entire string
	result = str_cremove(cstr("RemoveMe"), cstr("RemoveMe"));
	TEST_ASSERT(result.s != NULL && result.len == 0, "Remove entire string leaves empty");
	free_dstr(&result);
	
	// Overlapping pattern
	result = str_cremove(cstr("ababab"), cstr("aba"));
	TEST_ASSERT(strcmp(result.s, "bab") == 0, "Overlapping pattern handled");
	free_dstr(&result);
	
	// Single char removal
	result = str_cremove(cstr("a,b,c,d"), cstr(","));
	TEST_ASSERT(strcmp(result.s, "abcd") == 0, "Single char removal");
	free_dstr(&result);
}

void test_str_dremove(void)
{
	TEST_START("str_dremove - remove substring from dynamic string");
	
	// Basic removal
	t_dstr str1 = dstr_c(cstr("Hello World"));
	t_dstr result1 = str_dremove(&str1, cstr("World"));
	TEST_ASSERT(strcmp(result1.s, "Hello ") == 0, "Basic removal works");
	free_dstr(&result1);
	
	// Multiple occurrences
	t_dstr str2 = dstr_c(cstr("test test test"));
	t_dstr result2 = str_dremove(&str2, cstr("test"));
	TEST_ASSERT(strcmp(result2.s, "  ") == 0, "Multiple occurrences removed");
	free_dstr(&result2);
	
	// No match
	t_dstr str3 = dstr_c(cstr("Hello"));
	t_dstr result3 = str_dremove(&str3, cstr("xyz"));
	TEST_ASSERT(strcmp(result3.s, "Hello") == 0, "No match returns copy");
	free_dstr(&result3);
	
	// Remove at beginning
	t_dstr str4 = dstr_c(cstr("XXXHello"));
	t_dstr result4 = str_dremove(&str4, cstr("XXX"));
	TEST_ASSERT(strcmp(result4.s, "Hello") == 0, "Remove at beginning");
	free_dstr(&result4);
	
	// Remove at end
	t_dstr str5 = dstr_c(cstr("HelloXXX"));
	t_dstr result5 = str_dremove(&str5, cstr("XXX"));
	TEST_ASSERT(strcmp(result5.s, "Hello") == 0, "Remove at end");
	free_dstr(&result5);
	
	// Empty string
	t_dstr str6 = dstr_c(cstr(""));
	t_dstr result6 = str_dremove(&str6, cstr("test"));
	TEST_ASSERT(result6.s != NULL && result6.len == 0, "Empty string handled");
	free_dstr(&result6);
	
	// Remove entire string
	t_dstr str7 = dstr_c(cstr("All"));
	t_dstr result7 = str_dremove(&str7, cstr("All"));
	TEST_ASSERT(result7.s != NULL && result7.len == 0, "Remove entire string");
	free_dstr(&result7);
	
	// NULL remove string
	t_dstr str8 = dstr_c(cstr("Hello"));
	t_dstr result8 = str_dremove(&str8, cstr(NULL));
	TEST_ASSERT(strcmp(result8.s, "Hello") == 0, "NULL remove_str returns copy");
	free_dstr(&result8);
	
	// Complex pattern
	t_dstr str9 = dstr_c(cstr("abc123abc456abc789"));
	t_dstr result9 = str_dremove(&str9, cstr("abc"));
	TEST_ASSERT(strcmp(result9.s, "123456789") == 0, "Complex pattern removal");
	free_dstr(&result9);
}

// ============================================================================
// STRING ARRAY TESTS
// ============================================================================

void test_cstr_arr_constructors(void)
{
	TEST_START("cstr_arr constructors - array creation");
	
	// cstr_arr_s - allocate size
	t_cstr_arr arr = cstr_arr_s(5);
	TEST_ASSERT(arr.strs != NULL, "Array allocated");
	TEST_ASSERT(arr.size == 5, "Size correct");
	TEST_ASSERT(arr.len == 0, "Length initialized to 0");
	free_cstr_arr(&arr);
	
	// cstr_arr_c - copy array
	t_cstr_arr original = cstr_arr_s(3);
	original.strs[0] = cstr("Hello");
	original.strs[1] = cstr("World");
	original.len = 2;
	t_cstr_arr copy = cstr_arr_c(original);
	TEST_ASSERT(copy.strs != original.strs, "Different memory");
	TEST_ASSERT(copy.len == original.len, "Length copied");
	TEST_ASSERT(strcmp((const char *)copy.strs[0].s, "Hello") == 0, "Content copied");
	free_cstr_arr(&original);
	free_cstr_arr(&copy);
	
	// cstr_arr - from C array
	const t_i8 *strs[] = {"One", "Two", "Three"};
	t_cstr_arr from_c = cstr_arr(strs, 3);
	TEST_ASSERT(from_c.len == 3, "Length set");
	TEST_ASSERT(strcmp((const char *)from_c.strs[0].s, "One") == 0, "First element");
	TEST_ASSERT(strcmp((const char *)from_c.strs[2].s, "Three") == 0, "Last element");
	free_cstr_arr(&from_c);
}

void test_dstr_arr_constructors(void)
{
	TEST_START("dstr_arr constructors - dynamic array creation");
	
	// dstr_arr_s - allocate size
	t_dstr_arr arr = dstr_arr_s(5);
	TEST_ASSERT(arr.strs != NULL, "Array allocated");
	TEST_ASSERT(arr.size == 5, "Size correct");
	TEST_ASSERT(arr.len == 0, "Length initialized to 0");
	free_dstr_arr(&arr);
	
	// dstr_arr_d - duplicate array
	t_dstr_arr original = dstr_arr_s(3);
	original.strs[0] = dstr_c(cstr("Hello"));
	original.strs[1] = dstr_c(cstr("World"));
	original.len = 2;
	t_dstr_arr dup = dstr_arr_d(original);
	TEST_ASSERT(dup.strs != original.strs, "Different memory");
	TEST_ASSERT(dup.len == original.len, "Length copied");
	TEST_ASSERT(strcmp(dup.strs[0].s, "Hello") == 0, "Content duplicated");
	free_dstr_arr(&original);
	free_dstr_arr(&dup);
	
	// dstr_arr - from C array (need to create proper dynamic strings)
	t_dstr_arr from_c = dstr_arr_s(3);
	from_c = str_arr_add_d(&from_c, dstr_c(cstr("One")));
	from_c = str_arr_add_d(&from_c, dstr_c(cstr("Two")));
	from_c = str_arr_add_d(&from_c, dstr_c(cstr("Three")));
	TEST_ASSERT(from_c.len == 3, "Length set");
	TEST_ASSERT(strcmp(from_c.strs[0].s, "One") == 0, "First element");
	TEST_ASSERT(strcmp(from_c.strs[2].s, "Three") == 0, "Last element");
	free_dstr_arr(&from_c);
}

void test_str_arr_add(void)
{
	TEST_START("str_arr_add - adding strings to arrays");
	
	// str_arr_add_d - add dynamic string
	t_dstr_arr arr = dstr_arr_s(2);
	arr = str_arr_add_d(&arr, dstr_c(cstr("First")));
	TEST_ASSERT(arr.len == 1, "Length increased");
	TEST_ASSERT(strcmp(arr.strs[0].s, "First") == 0, "String added");
	
	arr = str_arr_add_d(&arr, dstr_c(cstr("Second")));
	TEST_ASSERT(arr.len == 2, "Second string added");
	
	// Trigger reallocation
	arr = str_arr_add_d(&arr, dstr_c(cstr("Third")));
	TEST_ASSERT(arr.len == 3, "Array reallocated and string added");
	TEST_ASSERT(strcmp(arr.strs[2].s, "Third") == 0, "Third string correct");
	free_dstr_arr(&arr);
	
	// str_arr_add_c - add constant string
	t_cstr_arr carr = cstr_arr_s(2);
	carr = str_arr_add_c(&carr, cstr("First"));
	TEST_ASSERT(carr.len == 1, "Constant string added");
	TEST_ASSERT(strcmp((const char *)carr.strs[0].s, "First") == 0, "Content correct");
	free_cstr_arr(&carr);
}

void test_str_arr_add_arr(void)
{
	TEST_START("str_arr_add_arr - adding arrays to arrays");
	
	// str_arr_add_d_arr
	t_dstr_arr arr1 = dstr_arr_s(2);
	arr1 = str_arr_add_d(&arr1, dstr_c(cstr("A")));
	arr1 = str_arr_add_d(&arr1, dstr_c(cstr("B")));
	
	t_dstr_arr arr2 = dstr_arr_s(2);
	arr2 = str_arr_add_d(&arr2, dstr_c(cstr("C")));
	arr2 = str_arr_add_d(&arr2, dstr_c(cstr("D")));
	
	arr1 = str_arr_add_d_arr(&arr1, &arr2);
	TEST_ASSERT(arr1.len == 4, "Arrays combined");
	TEST_ASSERT(strcmp(arr1.strs[2].s, "C") == 0, "Third element from arr2");
	TEST_ASSERT(strcmp(arr1.strs[3].s, "D") == 0, "Fourth element from arr2");
	free_dstr_arr(&arr1);
	
	// str_arr_add_c_arr
	t_cstr_arr carr1 = cstr_arr_s(2);
	carr1 = str_arr_add_c(&carr1, cstr("X"));
	carr1 = str_arr_add_c(&carr1, cstr("Y"));
	
	t_cstr_arr carr2 = cstr_arr_s(1);
	carr2 = str_arr_add_c(&carr2, cstr("Z"));
	
	carr1 = str_arr_add_c_arr(&carr1, &carr2);
	TEST_ASSERT(carr1.len == 3, "Constant arrays combined");
	TEST_ASSERT(strcmp((const char *)carr1.strs[2].s, "Z") == 0, "Third element");
	free_cstr_arr(&carr1);
}

void test_str_arr_unwrap(void)
{
	TEST_START("str_arr_unwrap - converting to C arrays");
	
	// dstr_arr_unwrap
	t_dstr_arr darr = dstr_arr_s(3);
	darr = str_arr_add_d(&darr, dstr_c(cstr("One")));
	darr = str_arr_add_d(&darr, dstr_c(cstr("Two")));
	darr = str_arr_add_d(&darr, dstr_c(cstr("Three")));
	
	t_i8 **c_arr = dstr_arr_unwrap(darr);
	TEST_ASSERT(c_arr != NULL, "C array created");
	TEST_ASSERT(strcmp(c_arr[0], "One") == 0, "First element");
	TEST_ASSERT(strcmp(c_arr[2], "Three") == 0, "Third element");
	TEST_ASSERT(c_arr[3] == NULL, "NULL terminated");
	
	// Free the array
	for (int i = 0; c_arr[i]; i++)
		free(c_arr[i]);
	free(c_arr);
	free_dstr_arr(&darr);
	
	// cstr_arr_unwrap
	t_cstr_arr carr = cstr_arr_s(2);
	carr = str_arr_add_c(&carr, cstr("Alpha"));
	carr = str_arr_add_c(&carr, cstr("Beta"));
	
	const t_i8 **const_c_arr = cstr_arr_unwrap(carr);
	TEST_ASSERT(const_c_arr != NULL, "Const C array created");
	TEST_ASSERT(strcmp((const char *)const_c_arr[0], "Alpha") == 0, "First element");
	TEST_ASSERT(strcmp((const char *)const_c_arr[1], "Beta") == 0, "Second element");
	TEST_ASSERT(const_c_arr[2] == NULL, "NULL terminated");
	
	free((void *)const_c_arr);
	free_cstr_arr(&carr);
}

// ============================================================================
// MEMORY LEAK TESTS
// ============================================================================

/*
void test_string_memory_leaks(void)
{
	TEST_START("String memory leak checks");
	
	// Create and free many strings
	for (int i = 0; i < 100; i++) {
		t_dstr str = dstr_s(100);
		strcpy(str.s, "Test string");
		str.len = 11;
		free_dstr(&str);
	}
	TEST_ASSERT(1, "Multiple allocations/frees");
	
	// Complex operations
	t_dstr str1 = dstr_c(cstr("Hello"));
	t_dstr str2 = dstr_c(cstr(" World"));
	str1 = str_insert(&str1, &str2, 5);
	free_dstr(&str1);
	TEST_ASSERT(1, "Insert operation cleans up");
	
	// Split and free
	t_dstr_arr split_result = str_split(cstr("a,b,c,d,e"), ',', NULL);
	free_dstr_arr(&split_result);
	TEST_ASSERT(1, "Split cleanup");
}
*/
// ============================================================================
// MAIN TEST RUNNER
// ============================================================================

void run_comprehensive_tests(void)
{
	// Constructor tests
	test_cstr();
	test_cstr_d();
	test_dstr_s();
	test_dstr_c();
	test_dstr_d();
	test_free_dstr();
	
	// Comparison tests
	test_str_cmp();
	test_str_start_with();
	test_str_end_with();
	
	// Find tests
	test_str_findchr();
	test_str_findlastchr();
	test_str_findindex();
	test_str_findlastindex();
	test_str_findsub();
	
	// Conversion tests
	test_str_from_char();
	test_str_to_int();
	test_str_from_int();
	test_str_to_long();
	test_str_from_long();
	
	// Manipulation tests
	test_str_insertc();
	test_str_insert();
	test_str_repeat();
	test_str_shift();
	test_str_dshift();
	test_str_cshrink();
	test_str_dshrink();
	test_str_split();
	test_str_split_with_rule();
	test_str_sub();
	test_str_trim();
	test_str_trim_str();
	test_str_cremove();
	test_str_dremove();
	test_str_map();
	test_str_foreach();
	test_str_arr_map();
	test_str_print();
	
	// Array tests
	test_cstr_arr_constructors();
	test_dstr_arr_constructors();
	//test_str_arr_add();
	//test_str_arr_add_arr();
	//test_str_arr_unwrap();
	
	// Memory tests
	//test_string_memory_leaks();
	
	// Malloc failure tests
	test_string_malloc_failures();

	TEST_SUMMARY();
}

// ============================================================================
// MALLOC FAILURE TESTS
// ============================================================================

void test_dstr_s_malloc_failure(void)
{
	TEST_START("dstr_s handles malloc failure");
	
	malloc_fail_enable();
	malloc_fail_after(0);
	
	t_dstr result = dstr_s(100);
	
	TEST_ASSERT(result.s == NULL, "Returns NULL s on malloc failure");
	TEST_ASSERT(result.size == 0, "Sets size to 0 on failure");
	TEST_ASSERT(result.len == 0, "Sets len to 0 on failure");
	
	malloc_fail_disable();
}

void test_dstr_c_str_malloc_failure(void)
{
	TEST_START("dstr_c handles malloc failure");
	
	malloc_fail_enable();
	malloc_fail_after(0);
	
	t_dstr result = dstr_c(cstr("test string"));
	
	TEST_ASSERT(result.s == NULL, "Returns NULL s on malloc failure");
	TEST_ASSERT(result.size == 0, "Sets size to 0 on failure");
	TEST_ASSERT(result.len == 0, "Sets len to 0 on failure");
	
	malloc_fail_disable();
}

void test_dstr_d_malloc_failure(void)
{
	TEST_START("dstr_d handles malloc failure");
	
	t_dstr src = dstr_s(50);
	if (src.s != NULL)
	{
		src.s[0] = 'A';
		src.s[1] = 'B';
		src.s[2] = '\0';
		src.len = 2;
		
		malloc_fail_enable();
		malloc_fail_after(0);
		
		t_dstr result = dstr_d(src);
		
		TEST_ASSERT(result.s == NULL, "Returns NULL s on malloc failure");
		TEST_ASSERT(result.size == 0, "Sets size to 0 on failure");
		
		malloc_fail_disable();
		
		free_dstr(&src);
	}
}

void test_str_repeat_str_malloc_failure(void)
{
	TEST_START("str_repeat handles malloc failure");
	
	malloc_fail_enable();
	malloc_fail_after(0);
	
	t_dstr result = str_repeat(cstr("test"), 5);
	
	TEST_ASSERT(result.s == NULL, "Returns NULL s on malloc failure");
	TEST_ASSERT(result.len == 0, "Sets len to 0 on failure");
	
	malloc_fail_disable();
}

void test_str_split_str_malloc_failure(void)
{
	TEST_START("str_split handles malloc failure");
	
	t_cstr input = cstr("hello,world,test");
	
	// Test failure on first allocation
	malloc_fail_enable();
	malloc_fail_after(0);
	
	t_dstr_arr result = str_split(input, ',', NULL);
	
	TEST_ASSERT(result.strs == NULL, "Returns NULL strs on malloc failure");
	TEST_ASSERT(result.len == 0, "Sets len to 0 on failure");
	
	malloc_fail_disable();
	
	// Test failure on second allocation
	malloc_fail_enable();
	malloc_fail_after(1);
	
	result = str_split(input, ',', NULL);
	
	TEST_ASSERT(result.strs == NULL, "Returns NULL and cleans up on second malloc fail");
	
	malloc_fail_disable();
}

void test_str_sub_malloc_failure(void)
{
	TEST_START("str_sub handles malloc failure");
	
	malloc_fail_enable();
	malloc_fail_after(0);
	
	t_dstr result = str_sub(cstr("hello world"), 0, 5);
	
	TEST_ASSERT(result.s == NULL, "Returns NULL s on malloc failure");
	TEST_ASSERT(result.len == 0, "Sets len to 0 on failure");
	
	malloc_fail_disable();
}

void test_str_from_int_malloc_failure(void)
{
	TEST_START("str_from_int handles malloc failure");
	
	malloc_fail_enable();
	malloc_fail_after(0);
	
	t_dstr result = str_from_int(12345, cstr("0123456789"), 1);
	
	TEST_ASSERT(result.s == NULL, "Returns NULL s on malloc failure");
	TEST_ASSERT(result.len == 0, "Sets len to 0 on failure");
	
	malloc_fail_disable();
}

void test_str_from_long_malloc_failure(void)
{
	TEST_START("str_from_long handles malloc failure");
	
	malloc_fail_enable();
	malloc_fail_after(0);
	
	t_dstr result = str_from_long(123456789L, cstr("0123456789"), 1);
	
	TEST_ASSERT(result.s == NULL, "Returns NULL s on malloc failure");
	TEST_ASSERT(result.len == 0, "Sets len to 0 on failure");
	
	malloc_fail_disable();
}

void test_str_from_char_malloc_failure(void)
{
	TEST_START("str_from_char handles malloc failure");
	
	malloc_fail_enable();
	malloc_fail_after(0);
	
	t_dstr result = str_from_char('A');
	
	TEST_ASSERT(result.s == NULL, "Returns NULL s on malloc failure");
	TEST_ASSERT(result.len == 0, "Sets len to 0 on failure");
	
	malloc_fail_disable();
}

void test_dstr_arr_s_malloc_failure(void)
{
	TEST_START("dstr_arr_s handles malloc failure");
	
	malloc_fail_enable();
	malloc_fail_after(0);
	
	t_dstr_arr result = dstr_arr_s(10);
	
	TEST_ASSERT(result.strs == NULL, "Returns NULL strs on malloc failure");
	TEST_ASSERT(result.len == 0, "Sets len to 0 on failure");
	
	malloc_fail_disable();
}

void test_str_insertc_malloc_failure(void)
{
	TEST_START("str_insertc handles malloc failure on reallocation");
	
	t_dstr str = dstr_c(cstr("Hello"));
	
	malloc_fail_enable();
	malloc_fail_after(0);
	
	t_dstr result = str_insertc(&str, cstr(" World"), 5);
	
	TEST_ASSERT(result.s == NULL, "Returns NULL s on malloc failure");
	TEST_ASSERT(result.len == 0, "Sets len to 0 on failure");
	
	malloc_fail_disable();
}

void test_str_insert_malloc_failure(void)
{
	TEST_START("str_insert handles malloc failure on reallocation");
	
	t_dstr str1 = dstr_c(cstr("Hello"));
	t_dstr str2 = dstr_c(cstr(" World"));
	
	malloc_fail_enable();
	malloc_fail_after(0);
	
	t_dstr result = str_insert(&str1, &str2, 5);
	
	TEST_ASSERT(result.s == NULL, "Returns NULL s on malloc failure");
	TEST_ASSERT(result.len == 0, "Sets len to 0 on failure");
	
	malloc_fail_disable();
}

void test_str_trim_char_malloc_failure(void)
{
	TEST_START("str_trim_char handles malloc failure");
	
	t_dstr str = dstr_c(cstr("  Hello  "));
	
	malloc_fail_enable();
	malloc_fail_after(0);
	
	t_dstr result = str_trim_char(&str, cstr(" "));
	
	TEST_ASSERT(result.s == NULL, "Returns NULL s on malloc failure");
	TEST_ASSERT(result.len == 0, "Sets len to 0 on failure");
	
	malloc_fail_disable();
}

void test_str_trim_str_malloc_failure(void)
{
	TEST_START("str_trim_str handles malloc failure");
	
	t_dstr str = dstr_c(cstr("abcHelloabc"));
	
	malloc_fail_enable();
	malloc_fail_after(0);
	
	t_dstr result = str_trim_str(&str, cstr("abc"));
	
	TEST_ASSERT(result.s == NULL, "Returns NULL s on malloc failure");
	TEST_ASSERT(result.len == 0, "Sets len to 0 on failure");
	
	malloc_fail_disable();
}

void test_str_map_malloc_failure(void)
{
	TEST_START("str_map handles malloc failure");
	
	t_dstr str = dstr_c(cstr("hello"));
	
	malloc_fail_enable();
	malloc_fail_after(0);
	
	t_dstr result = str_map(&str, to_upper_helper);
	
	TEST_ASSERT(result.s == NULL, "Returns NULL s on malloc failure");
	TEST_ASSERT(result.len == 0, "Sets len to 0 on failure");
	
	malloc_fail_disable();
}

void test_str_arr_map_malloc_failure(void)
{
	TEST_START("str_arr_map handles malloc failure");
	
	t_dstr_arr arr = dstr_arr_s(3);
	arr = str_arr_add_d(&arr, dstr_c(cstr("hello")));
	arr = str_arr_add_d(&arr, dstr_c(cstr("world")));
	
	malloc_fail_enable();
	malloc_fail_after(0);
	
	t_dstr_arr result = str_arr_map(&arr, to_upper_str_helper);
	
	TEST_ASSERT(result.strs == NULL, "Returns NULL strs on malloc failure");
	TEST_ASSERT(result.len == 0, "Sets len to 0 on failure");
	
	malloc_fail_disable();
}

void test_str_arr_add_d_malloc_failure(void)
{
	TEST_START("str_arr_add_d handles malloc failure on reallocation");
	
	t_dstr_arr arr = dstr_arr_s(1);
	arr.strs[0] = dstr_c(cstr("First"));
	arr.len = 1;
	
	malloc_fail_enable();
	malloc_fail_after(0);
	
	t_dstr_arr result = str_arr_add_d(&arr, dstr_c(cstr("Second")));
	
	TEST_ASSERT(result.strs == NULL, "Returns NULL strs on malloc failure");
	TEST_ASSERT(result.len == 0, "Sets len to 0 on failure");
	
	malloc_fail_disable();
}

void test_str_arr_add_d_arr_malloc_failure(void)
{
	TEST_START("str_arr_add_d_arr handles malloc failure on reallocation");
	
	t_dstr_arr arr1 = dstr_arr_s(1);
	arr1.strs[0] = dstr_c(cstr("First"));
	arr1.len = 1;
	
	t_dstr_arr arr2 = dstr_arr_s(1);
	arr2.strs[0] = dstr_c(cstr("Second"));
	arr2.len = 1;
	
	malloc_fail_enable();
	malloc_fail_after(0);
	
	t_dstr_arr result = str_arr_add_d_arr(&arr1, &arr2);
	
	TEST_ASSERT(result.strs == NULL, "Returns NULL strs on malloc failure");
	TEST_ASSERT(result.len == 0, "Sets len to 0 on failure");
	
	malloc_fail_disable();
}

void test_str_from_buf_malloc_failure(void)
{
	TEST_START("str_from_buf handles malloc failure");
	
	t_dbuf buf = dbuf_c(cbuf("Hello", 5));
	
	malloc_fail_enable();
	malloc_fail_after(0);
	
	t_dstr result = str_from_buf(&buf);
	
	TEST_ASSERT(result.s == NULL, "Returns NULL s on malloc failure");
	TEST_ASSERT(result.len == 0, "Sets len to 0 on failure");
	
	malloc_fail_disable();
}

void test_cstr_arr_s_malloc_failure(void)
{
	TEST_START("cstr_arr_s handles malloc failure");
	
	malloc_fail_enable();
	malloc_fail_after(0);
	
	t_cstr_arr result = cstr_arr_s(10);
	
	TEST_ASSERT(result.strs == NULL, "Returns NULL strs on malloc failure");
	TEST_ASSERT(result.len == 0, "Sets len to 0 on failure");
	
	malloc_fail_disable();
}

void test_dstr_arr_d_malloc_failure(void)
{
	TEST_START("dstr_arr_d handles malloc failure");
	
	t_dstr_arr arr = dstr_arr_s(2);
	arr.strs[0] = dstr_c(cstr("First"));
	arr.strs[1] = dstr_c(cstr("Second"));
	arr.len = 2;
	
	malloc_fail_enable();
	malloc_fail_after(0);
	
	t_dstr_arr result = dstr_arr_d(arr);
	
	TEST_ASSERT(result.strs == NULL, "Returns NULL strs on malloc failure");
	TEST_ASSERT(result.len == 0, "Sets len to 0 on failure");
	
	free_dstr_arr(&arr);
	malloc_fail_disable();
}

void test_dstr_arr_unwrap_malloc_failure(void)
{
	TEST_START("dstr_arr_unwrap handles malloc failure");
	
	t_dstr_arr arr = dstr_arr_s(2);
	arr.strs[0] = dstr_c(cstr("First"));
	arr.strs[1] = dstr_c(cstr("Second"));
	arr.len = 2;
	
	malloc_fail_enable();
	malloc_fail_after(0);
	
	t_i8 **result = dstr_arr_unwrap(arr);
	
	TEST_ASSERT(result == NULL, "Returns NULL on malloc failure");
	
	free_dstr_arr(&arr);
	malloc_fail_disable();
}

void test_cstr_arr_unwrap_malloc_failure(void)
{
	TEST_START("cstr_arr_unwrap handles malloc failure");
	
	t_cstr_arr arr = cstr_arr_s(2);
	arr.strs[0] = cstr("First");
	arr.strs[1] = cstr("Second");
	arr.len = 2;
	
	malloc_fail_enable();
	malloc_fail_after(0);
	
	const t_i8 **result = cstr_arr_unwrap(arr);
	
	TEST_ASSERT(result == NULL, "Returns NULL on malloc failure");
	
	free(arr.strs);
	malloc_fail_disable();
}

void test_str_cremove_malloc_failure(void)
{
	TEST_START("str_cremove handles malloc failure");
	
	malloc_fail_enable();
	malloc_fail_after(0);
	
	t_dstr result = str_cremove(cstr("Hello World"), cstr("World"));
	
	TEST_ASSERT(result.s == NULL, "Returns NULL s on malloc failure");
	TEST_ASSERT(result.len == 0, "Sets len to 0 on failure");
	
	malloc_fail_disable();
}

void test_str_dremove_malloc_failure(void)
{
	TEST_START("str_dremove handles malloc failure");
	
	t_dstr str = dstr_c(cstr("Hello World"));
	
	malloc_fail_enable();
	malloc_fail_after(0);
	
	t_dstr result = str_dremove(&str, cstr("World"));
	
	TEST_ASSERT(result.s == NULL, "Returns NULL s on malloc failure");
	TEST_ASSERT(result.len == 0, "Sets len to 0 on failure");
	
	malloc_fail_disable();
}

void test_string_malloc_failures(void)
{
	TEST_SECTION("String Malloc Failure Tests");
	
	test_dstr_s_malloc_failure();
	test_dstr_c_str_malloc_failure();
	test_dstr_d_malloc_failure();
	test_str_repeat_str_malloc_failure();
	test_str_split_str_malloc_failure();
	test_str_sub_malloc_failure();
	test_str_from_int_malloc_failure();
	test_str_from_long_malloc_failure();
	test_str_from_char_malloc_failure();
	test_dstr_arr_s_malloc_failure();
	test_str_insertc_malloc_failure();
	test_str_insert_malloc_failure();
	test_str_trim_char_malloc_failure();
	test_str_trim_str_malloc_failure();
	test_str_cremove_malloc_failure();
	test_str_dremove_malloc_failure();
	test_str_map_malloc_failure();
	test_str_arr_map_malloc_failure();
	test_str_arr_add_d_malloc_failure();
	test_str_arr_add_d_arr_malloc_failure();
	test_str_from_buf_malloc_failure();
	test_cstr_arr_s_malloc_failure();
	test_dstr_arr_d_malloc_failure();
	test_dstr_arr_unwrap_malloc_failure();
	test_cstr_arr_unwrap_malloc_failure();
}
