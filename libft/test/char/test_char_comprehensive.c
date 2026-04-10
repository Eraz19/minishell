/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_char_comprehensive.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: GitHub Copilot                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 19:00:00 by Copilot           #+#    #+#             */
/*   Updated: 2026/01/19 19:00:00 by Copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_test.h"
#include "libft.h"


// Override TEST_ASSERT and TEST_SUMMARY to use char-specific counters
#undef TEST_ASSERT
#define TEST_ASSERT CHAR_TEST_ASSERT
#undef TEST_SUMMARY
#define TEST_SUMMARY CHAR_TEST_SUMMARY

// Test counters (shared across test files)
int g_char_tests_run = 0;
int g_char_tests_passed = 0;
int g_char_tests_failed = 0;

// ============================================================================
// CHARACTER CLASSIFICATION TESTS
// ============================================================================

void test_c_isalpha(void)
{
	TEST_START("c_isalpha - alphabetic character check");
	
	// Lowercase letters
	TEST_ASSERT(c_isalpha('a') == TRUE, "Lowercase 'a' is alpha");
	TEST_ASSERT(c_isalpha('z') == TRUE, "Lowercase 'z' is alpha");
	TEST_ASSERT(c_isalpha('m') == TRUE, "Lowercase 'm' is alpha");
	
	// Uppercase letters
	TEST_ASSERT(c_isalpha('A') == TRUE, "Uppercase 'A' is alpha");
	TEST_ASSERT(c_isalpha('Z') == TRUE, "Uppercase 'Z' is alpha");
	TEST_ASSERT(c_isalpha('M') == TRUE, "Uppercase 'M' is alpha");
	
	// Non-alphabetic
	TEST_ASSERT(c_isalpha('0') == FALSE, "Digit '0' is not alpha");
	TEST_ASSERT(c_isalpha('9') == FALSE, "Digit '9' is not alpha");
	TEST_ASSERT(c_isalpha(' ') == FALSE, "Space is not alpha");
	TEST_ASSERT(c_isalpha('!') == FALSE, "Punctuation '!' is not alpha");
	TEST_ASSERT(c_isalpha('\n') == FALSE, "Newline is not alpha");
	TEST_ASSERT(c_isalpha('\0') == FALSE, "Null byte is not alpha");
	
	// Edge cases
	TEST_ASSERT(c_isalpha('@') == FALSE, "Character before 'A' is not alpha");
	TEST_ASSERT(c_isalpha('[') == FALSE, "Character after 'Z' is not alpha");
	TEST_ASSERT(c_isalpha('`') == FALSE, "Character before 'a' is not alpha");
	TEST_ASSERT(c_isalpha('{') == FALSE, "Character after 'z' is not alpha");
}

void test_c_isdigit(void)
{
	TEST_START("c_isdigit - digit character check");
	
	// Digits
	TEST_ASSERT(c_isdigit('0') == TRUE, "Character '0' is digit");
	TEST_ASSERT(c_isdigit('1') == TRUE, "Character '1' is digit");
	TEST_ASSERT(c_isdigit('5') == TRUE, "Character '5' is digit");
	TEST_ASSERT(c_isdigit('9') == TRUE, "Character '9' is digit");
	
	// Non-digits
	TEST_ASSERT(c_isdigit('a') == FALSE, "Lowercase letter is not digit");
	TEST_ASSERT(c_isdigit('Z') == FALSE, "Uppercase letter is not digit");
	TEST_ASSERT(c_isdigit(' ') == FALSE, "Space is not digit");
	TEST_ASSERT(c_isdigit('\n') == FALSE, "Newline is not digit");
	TEST_ASSERT(c_isdigit('\0') == FALSE, "Null byte is not digit");
	
	// Edge cases
	TEST_ASSERT(c_isdigit('/') == FALSE, "Character before '0' is not digit");
	TEST_ASSERT(c_isdigit(':') == FALSE, "Character after '9' is not digit");
}

void test_c_isalnum(void)
{
	TEST_START("c_isalnum - alphanumeric character check");
	
	// Alphanumeric
	TEST_ASSERT(c_isalnum('a') == TRUE, "Lowercase letter is alnum");
	TEST_ASSERT(c_isalnum('Z') == TRUE, "Uppercase letter is alnum");
	TEST_ASSERT(c_isalnum('0') == TRUE, "Digit '0' is alnum");
	TEST_ASSERT(c_isalnum('9') == TRUE, "Digit '9' is alnum");
	TEST_ASSERT(c_isalnum('m') == TRUE, "Lowercase 'm' is alnum");
	TEST_ASSERT(c_isalnum('5') == TRUE, "Digit '5' is alnum");
	
	// Non-alphanumeric
	TEST_ASSERT(c_isalnum(' ') == FALSE, "Space is not alnum");
	TEST_ASSERT(c_isalnum('!') == FALSE, "Punctuation is not alnum");
	TEST_ASSERT(c_isalnum('\n') == FALSE, "Newline is not alnum");
	TEST_ASSERT(c_isalnum('\t') == FALSE, "Tab is not alnum");
	TEST_ASSERT(c_isalnum('@') == FALSE, "Symbol '@' is not alnum");
	TEST_ASSERT(c_isalnum('#') == FALSE, "Symbol '#' is not alnum");
}

void test_c_isascii(void)
{
	TEST_START("c_isascii - ASCII character check");
	
	// Valid ASCII (0-127)
	TEST_ASSERT(c_isascii(0) == TRUE, "Null byte is ASCII");
	TEST_ASSERT(c_isascii(1) == TRUE, "Character 1 is ASCII");
	TEST_ASSERT(c_isascii(32) == TRUE, "Space (32) is ASCII");
	TEST_ASSERT(c_isascii('A') == TRUE, "Letter 'A' is ASCII");
	TEST_ASSERT(c_isascii('z') == TRUE, "Letter 'z' is ASCII");
	TEST_ASSERT(c_isascii('0') == TRUE, "Digit '0' is ASCII");
	TEST_ASSERT(c_isascii(127) == TRUE, "DEL (127) is ASCII");
	
	// Invalid ASCII (outside 0-127)
	TEST_ASSERT(c_isascii(128) == FALSE, "Character 128 is not ASCII");
	TEST_ASSERT(c_isascii(255) == FALSE, "Character 255 is not ASCII");
	TEST_ASSERT(c_isascii(-1) == FALSE, "Negative value is not ASCII");
	TEST_ASSERT(c_isascii(200) == FALSE, "Character 200 is not ASCII");
}

void test_c_isprint(void)
{
	TEST_START("c_isprint - printable character check");
	
	// Printable characters (32-126)
	TEST_ASSERT(c_isprint(' ') == TRUE, "Space is printable");
	TEST_ASSERT(c_isprint('!') == TRUE, "Character '!' is printable");
	TEST_ASSERT(c_isprint('A') == TRUE, "Letter 'A' is printable");
	TEST_ASSERT(c_isprint('z') == TRUE, "Letter 'z' is printable");
	TEST_ASSERT(c_isprint('0') == TRUE, "Digit '0' is printable");
	TEST_ASSERT(c_isprint('~') == TRUE, "Character '~' is printable");
	
	// Non-printable characters
	TEST_ASSERT(c_isprint('\0') == FALSE, "Null byte is not printable");
	TEST_ASSERT(c_isprint('\n') == FALSE, "Newline is not printable");
	TEST_ASSERT(c_isprint('\t') == FALSE, "Tab is not printable");
	TEST_ASSERT(c_isprint(31) == FALSE, "Character 31 is not printable");
	TEST_ASSERT(c_isprint(127) == FALSE, "DEL (127) is not printable");
	TEST_ASSERT(c_isprint(128) == FALSE, "Character 128 is not printable");
}

void test_c_isspace(void)
{
	TEST_START("c_isspace - whitespace character check");
	
	// Whitespace characters
	TEST_ASSERT(c_isspace(' ') == TRUE, "Space is whitespace");
	TEST_ASSERT(c_isspace('\t') == TRUE, "Tab is whitespace");
	TEST_ASSERT(c_isspace('\n') == TRUE, "Newline is whitespace");
	TEST_ASSERT(c_isspace('\v') == TRUE, "Vertical tab is whitespace");
	TEST_ASSERT(c_isspace('\f') == TRUE, "Form feed is whitespace");
	TEST_ASSERT(c_isspace('\r') == TRUE, "Carriage return is whitespace");
	
	// Non-whitespace characters
	TEST_ASSERT(c_isspace('a') == FALSE, "Letter 'a' is not whitespace");
	TEST_ASSERT(c_isspace('0') == FALSE, "Digit '0' is not whitespace");
	TEST_ASSERT(c_isspace('\0') == FALSE, "Null byte is not whitespace");
	TEST_ASSERT(c_isspace('!') == FALSE, "Punctuation is not whitespace");
}

// ============================================================================
// CHARACTER CONVERSION TESTS
// ============================================================================

void test_c_toupper(void)
{
	TEST_START("c_toupper - uppercase conversion");
	
	// Lowercase to uppercase
	TEST_ASSERT(c_toupper('a') == 'A', "Lowercase 'a' converts to 'A'");
	TEST_ASSERT(c_toupper('z') == 'Z', "Lowercase 'z' converts to 'Z'");
	TEST_ASSERT(c_toupper('m') == 'M', "Lowercase 'm' converts to 'M'");
	
	// Already uppercase (no change)
	TEST_ASSERT(c_toupper('A') == 'A', "Uppercase 'A' stays 'A'");
	TEST_ASSERT(c_toupper('Z') == 'Z', "Uppercase 'Z' stays 'Z'");
	
	// Non-alphabetic (no change)
	TEST_ASSERT(c_toupper('0') == '0', "Digit '0' unchanged");
	TEST_ASSERT(c_toupper('9') == '9', "Digit '9' unchanged");
	TEST_ASSERT(c_toupper(' ') == ' ', "Space unchanged");
	TEST_ASSERT(c_toupper('!') == '!', "Punctuation unchanged");
	TEST_ASSERT(c_toupper('\n') == '\n', "Newline unchanged");
	TEST_ASSERT(c_toupper('@') == '@', "Symbol '@' unchanged");
}

void test_c_tolower(void)
{
	TEST_START("c_tolower - lowercase conversion");
	
	// Uppercase to lowercase
	TEST_ASSERT(c_tolower('A') == 'a', "Uppercase 'A' converts to 'a'");
	TEST_ASSERT(c_tolower('Z') == 'z', "Uppercase 'Z' converts to 'z'");
	TEST_ASSERT(c_tolower('M') == 'm', "Uppercase 'M' converts to 'm'");
	
	// Already lowercase (no change)
	TEST_ASSERT(c_tolower('a') == 'a', "Lowercase 'a' stays 'a'");
	TEST_ASSERT(c_tolower('z') == 'z', "Lowercase 'z' stays 'z'");
	
	// Non-alphabetic (no change)
	TEST_ASSERT(c_tolower('0') == '0', "Digit '0' unchanged");
	TEST_ASSERT(c_tolower('9') == '9', "Digit '9' unchanged");
	TEST_ASSERT(c_tolower(' ') == ' ', "Space unchanged");
	TEST_ASSERT(c_tolower('!') == '!', "Punctuation unchanged");
	TEST_ASSERT(c_tolower('\n') == '\n', "Newline unchanged");
	TEST_ASSERT(c_tolower('[') == '[', "Symbol '[' unchanged");
}

void test_c_ishexdigit(void)
{
	TEST_START("c_ishexdigit - hexadecimal digit check");
	
	// Decimal digits
	TEST_ASSERT(c_ishexdigit('0') == TRUE, "Character '0' is hexdigit");
	TEST_ASSERT(c_ishexdigit('5') == TRUE, "Character '5' is hexdigit");
	TEST_ASSERT(c_ishexdigit('9') == TRUE, "Character '9' is hexdigit");
	
	// Uppercase hex digits
	TEST_ASSERT(c_ishexdigit('A') == TRUE, "Character 'A' is hexdigit");
	TEST_ASSERT(c_ishexdigit('F') == TRUE, "Character 'F' is hexdigit");
	TEST_ASSERT(c_ishexdigit('C') == TRUE, "Character 'C' is hexdigit");
	
	// Lowercase hex digits
	TEST_ASSERT(c_ishexdigit('a') == TRUE, "Character 'a' is hexdigit");
	TEST_ASSERT(c_ishexdigit('f') == TRUE, "Character 'f' is hexdigit");
	TEST_ASSERT(c_ishexdigit('d') == TRUE, "Character 'd' is hexdigit");
	
	// Non-hexadecimal
	TEST_ASSERT(c_ishexdigit('G') == FALSE, "Character 'G' is not hexdigit");
	TEST_ASSERT(c_ishexdigit('g') == FALSE, "Character 'g' is not hexdigit");
	TEST_ASSERT(c_ishexdigit('Z') == FALSE, "Character 'Z' is not hexdigit");
	TEST_ASSERT(c_ishexdigit(' ') == FALSE, "Space is not hexdigit");
	TEST_ASSERT(c_ishexdigit('!') == FALSE, "Punctuation is not hexdigit");
	TEST_ASSERT(c_ishexdigit('\n') == FALSE, "Newline is not hexdigit");
}

void test_c_isuppercase(void)
{
	TEST_START("c_isuppercase - uppercase letter check");
	
	// Uppercase letters
	TEST_ASSERT(c_isuppercase('A') == TRUE, "Character 'A' is uppercase");
	TEST_ASSERT(c_isuppercase('Z') == TRUE, "Character 'Z' is uppercase");
	TEST_ASSERT(c_isuppercase('M') == TRUE, "Character 'M' is uppercase");
	TEST_ASSERT(c_isuppercase('H') == TRUE, "Character 'H' is uppercase");
	
	// Lowercase letters
	TEST_ASSERT(c_isuppercase('a') == FALSE, "Character 'a' is not uppercase");
	TEST_ASSERT(c_isuppercase('z') == FALSE, "Character 'z' is not uppercase");
	TEST_ASSERT(c_isuppercase('m') == FALSE, "Character 'm' is not uppercase");
	
	// Non-alphabetic
	TEST_ASSERT(c_isuppercase('0') == FALSE, "Digit '0' is not uppercase");
	TEST_ASSERT(c_isuppercase('9') == FALSE, "Digit '9' is not uppercase");
	TEST_ASSERT(c_isuppercase(' ') == FALSE, "Space is not uppercase");
	TEST_ASSERT(c_isuppercase('!') == FALSE, "Punctuation is not uppercase");
	TEST_ASSERT(c_isuppercase('\n') == FALSE, "Newline is not uppercase");
}

void test_c_islowercase(void)
{
	TEST_START("c_islowercase - lowercase letter check");
	
	// Lowercase letters
	TEST_ASSERT(c_islowercase('a') == TRUE, "Character 'a' is lowercase");
	TEST_ASSERT(c_islowercase('z') == TRUE, "Character 'z' is lowercase");
	TEST_ASSERT(c_islowercase('m') == TRUE, "Character 'm' is lowercase");
	TEST_ASSERT(c_islowercase('h') == TRUE, "Character 'h' is lowercase");
	
	// Uppercase letters
	TEST_ASSERT(c_islowercase('A') == FALSE, "Character 'A' is not lowercase");
	TEST_ASSERT(c_islowercase('Z') == FALSE, "Character 'Z' is not lowercase");
	TEST_ASSERT(c_islowercase('M') == FALSE, "Character 'M' is not lowercase");
	
	// Non-alphabetic
	TEST_ASSERT(c_islowercase('0') == FALSE, "Digit '0' is not lowercase");
	TEST_ASSERT(c_islowercase('9') == FALSE, "Digit '9' is not lowercase");
	TEST_ASSERT(c_islowercase(' ') == FALSE, "Space is not lowercase");
	TEST_ASSERT(c_islowercase('!') == FALSE, "Punctuation is not lowercase");
	TEST_ASSERT(c_islowercase('\n') == FALSE, "Newline is not lowercase");
}

// ============================================================================
// MAIN TEST RUNNER
// ============================================================================

void run_char_comprehensive_tests(void)
{	
	test_c_isalpha();
	test_c_isdigit();
	test_c_isalnum();
	test_c_isascii();
	test_c_isprint();
	test_c_isspace();
	test_c_toupper();
	test_c_tolower();
	test_c_ishexdigit();
	test_c_isuppercase();
	test_c_islowercase();
	
	TEST_SUMMARY();
}
