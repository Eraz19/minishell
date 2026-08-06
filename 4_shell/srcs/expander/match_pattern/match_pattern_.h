/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_pattern_.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:44:47 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/06 00:34:19 by adouieb          ###   ########.fr       */
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

/* ************************************************************************* */
/*                                  ENGINE                                   */
/* ************************************************************************* */

/**
 * @ingroup expander_match
 * @brief Matches a pattern starting with @c * : swallows the star run,
 *        then tries the pattern tail at every offset of @p str.
 *
 * @param pattern Rendered pattern starting at the @c * (borrowed,
 *                read-only).
 * @param str Characters to match (borrowed, read-only).
 * @param len Number of characters of @p str to match.
 */
bool	match_asterisk(const char *pattern, const char *str, size_t len);

/**
 * @ingroup expander_match
 * @brief Matches a pattern starting with @c [ : evaluates the bracket
 *        expression against the first character, then the pattern tail
 *        against the rest; an invalid bracket expression degrades to a
 *        literal @c [ (POSIX 2.13.1).
 *
 * @param pattern Rendered pattern starting at the @c [ (borrowed,
 *                read-only).
 * @param str Characters to match (borrowed, read-only).
 * @param len Number of characters of @p str to match.
 */
bool	match_bracket(const char *pattern, const char *str, size_t len);

/**
 * @ingroup expander_match
 * @brief Tells whether the bracket expression of @p pattern (of body
 *        length @p len, negation already consumed) matches @p c,
 *        honoring the leading @c ! / @c ^ negation.
 *
 * @param pattern Rendered pattern starting at the @c [ (borrowed,
 *                read-only).
 * @param len Length of the bracket expression body.
 * @param c Character to match.
 */
bool	match_bracket_c(const char *pattern, size_t len, char c);

/**
 * @ingroup expander_match
 * @brief Compares one pattern character with one subject character and
 *        advances the pattern index on match.
 *
 * @param c1 Pattern character.
 * @param c2 Subject character.
 * @param len Pattern index, advanced on match (borrowed).
 */
bool	match_char(char c1, char c2, size_t *len);

/**
 * @ingroup expander_match
 * @brief Consumes the leading @c ! or @c ^ of a bracket expression body.
 *
 * @param pattern Rendered pattern (borrowed, read-only).
 * @param i Index of the body start, advanced past the negation
 *          (borrowed).
 * @return @c true when a negation was consumed.
 */
bool	set_negation(const char *pattern, size_t *i);

/* ************************************************************************* */
/*                                EVALUATION                                 */
/* ************************************************************************* */

/**
 * @ingroup expander_match
 * @brief Evaluates one plain set character of a bracket expression
 *        against @p c, advancing @p i.
 *
 * @param pattern Rendered pattern (borrowed, read-only).
 * @param c Character to match.
 * @param i Index of the set character, advanced (borrowed).
 */
bool	eval_bracket_char(const char *pattern, char c, size_t *i);

/**
 * @ingroup expander_match
 * @brief Evaluates a backslash-escaped set character against @p c,
 *        skipping the backslash first.
 *
 * @param pattern Rendered pattern (borrowed, read-only).
 * @param c Character to match.
 * @param i Index of the backslash, advanced past the pair (borrowed).
 */
bool	eval_escaped_char(const char *pattern, char c, size_t *i);

/**
 * @ingroup expander_match
 * @brief Evaluates a range expression @c a-z against @p c, comparing the
 *        byte encodings as unsigned values (POSIX 2.13.1, C locale).
 *
 * @param pattern Rendered pattern positioned on the range start
 *                (borrowed, read-only).
 * @param c Character to match.
 * @param i Index of the range start, advanced past the range (borrowed).
 */
bool	eval_range(const char *pattern, char c, size_t *i);

/**
 * @ingroup expander_match
 * @brief Evaluates a @c [: @c [. @c [= sub-expression against @p c
 *        (character classes; collating symbols and equivalence classes
 *        degrade to their literal characters).
 *
 * @param pattern Rendered pattern positioned on the sub-expression
 *                (borrowed, read-only).
 * @param c Character to match.
 * @param i Index of the sub-expression, advanced past it (borrowed).
 */
bool	eval_sub_exp(const char *pattern, char c, size_t *i);

/* ************************************************************************* */
/*                                VALIDATION                                 */
/* ************************************************************************* */

/**
 * @ingroup expander_match
 * @brief Measures a whole bracket expression body: negation, leading
 *        @c ] literal, sets, ranges and sub-expressions, up to the
 *        closing @c ].
 *
 * @param pattern Rendered pattern positioned after the @c [ (borrowed,
 *                read-only).
 * @param len Set to the body length (borrowed).
 * @return @c false when the expression never closes (the @c [ is then a
 *         literal).
 */
bool	valid_bracket_exp_len(const char *pattern, size_t *len);

/**
 * @ingroup expander_match
 * @brief Measures a @c [:class:] sub-expression and validates the class
 *        name.
 *
 * @param pattern Rendered pattern positioned on the sub-expression
 *                (borrowed, read-only).
 * @param len Advanced past the sub-expression (borrowed).
 */
bool	valid_char_class_exp_len(const char *pattern, size_t *len);

/**
 * @ingroup expander_match
 * @brief Measures a @c [.symbol.] collating-symbol sub-expression.
 *
 * @param pattern Rendered pattern positioned on the sub-expression
 *                (borrowed, read-only).
 * @param len Advanced past the sub-expression (borrowed).
 */
bool	valid_col_symbol_exp_len(const char *pattern, size_t *len);

/**
 * @ingroup expander_match
 * @brief Measures a @c [=equiv=] equivalence-class sub-expression.
 *
 * @param pattern Rendered pattern positioned on the sub-expression
 *                (borrowed, read-only).
 * @param len Advanced past the sub-expression (borrowed).
 */
bool	valid_equ_class_exp_len(const char *pattern, size_t *len);

/**
 * @ingroup expander_match
 * @brief Measures any @c [: @c [. @c [= sub-expression, dispatching to
 *        the matching validator.
 *
 * @param pattern Rendered pattern positioned on the sub-expression
 *                (borrowed, read-only).
 * @param len Advanced past the sub-expression (borrowed).
 */
bool	valid_sub_exp_len(const char *pattern, size_t *len);

/* ************************************************************************* */
/*                                  UTILS                                    */
/* ************************************************************************* */

/**
 * @ingroup expander_match
 * @brief Tells whether @p c is a hexadecimal digit.
 *
 * @param c Character to test.
 */
bool	ft_isxdigit(char c);

#endif
