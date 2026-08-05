/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_pattern_.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:44:47 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/05 15:50:23 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATCH_PATTERN__H
# define MATCH_PATTERN__H

# include <stddef.h>
# include <stdbool.h>

/** @defgroup expander_match Pattern matching
 *  @brief POSIX 2.13 pattern matching engine and its quoting-aware
 *         front ends.
 *
 *  The char engine (@c match_pattern) works on a rendered dialect where
 *  a backslash makes the next character literal; quoting decisions are
 *  taken upstream by @c pattern_from_word, which renders an annotated
 *  word so that quoted or escaped metacharacters (POSIX 2.13.1) are
 *  backslash-escaped and unquoted ones stay active. @c word_match_pattern
 *  combines both for single-shot matches (a @c case pattern); loop
 *  matchers (@c ${var#pat}, pathname expansion) render once and drive
 *  the engine directly.
 */

bool	match_bracket(const char *pattern, const char *str, size_t len);
bool	match_asterisk(const char *pattern, const char *str, size_t len);

bool	valid_bracket_exp_len(const char *pattern, size_t *len);
bool	match_bracket_c(const char *pattern, size_t len, char c);

bool	ft_isxdigit(char c);
bool	match_char(char c1, char c2, size_t *len);
bool	set_negation(const char *pattern, size_t *i);
bool	valid_sub_exp_len(const char *pattern, size_t *len);

bool	eval_range(const char *pattern, char c, size_t *i);
bool	eval_sub_exp(const char *pattern, char c, size_t *i);
bool	eval_bracket_char(const char *pattern, char c, size_t *i);
bool	eval_escaped_char(const char *pattern, char c, size_t *i);

bool	valid_equ_class_exp_len(const char *pattern, size_t *len);
bool	valid_char_class_exp_len(const char *pattern, size_t *len);
bool	valid_col_symbol_exp_len(const char *pattern, size_t *len);

#endif
