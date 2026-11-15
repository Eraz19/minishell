/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_squote_expansion_.h                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:46:47 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 17:46:48 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOLLAR_SQUOTE_EXPANSION__H
# define DOLLAR_SQUOTE_EXPANSION__H

# include "expander_.h"

/** @defgroup expander_dollar_squote Expander dollar-single-quote expansion
 *  @brief The $'...' ANSI-C quoting form: backslash escape sequences of
 *         the body are translated into literal characters, emitted as
 *         expansion results.
 */

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup expander_dollar_squote
 * @brief Fills @p escapes with the single-letter escapes (a, b, e, f, n,
 *        r, t, v, backslash, single and double quote) mapped to the byte
 *        each one decodes to.
 *
 * @param escapes Map initialized by the function, freed again on failure
 *                (borrowed).
 * @return @c true on success, @c false on allocation failure.
 */
bool			dollar_squote_build_map(t_hashmap *escapes);

/**
 * @ingroup expander_dollar_squote
 * @brief Converts @p c to its digit value in base @p base.
 *
 * @param c Candidate digit character.
 * @param base Numeric base, up to 16.
 * @return The digit value, or @c -1 when @p c is not a digit of
 *         @p base.
 */
int				dollar_squote_digit(char c, int base);

/**
 * @ingroup expander_dollar_squote
 * @brief Discards the remaining body items of the construct, up to (and
 *        excluding) the closing quote: the POSIX 2.2.4 behavior applied
 *        when an escape decodes to a NUL byte.
 *
 * @param expander Expander state whose word is consumed (borrowed).
 * @return @c ERR_NO.
 */
t_error			dollar_squote_discard_rest(t_expander *expander);

/**
 * @ingroup expander_dollar_squote
 * @brief Applies a control escape ( \cX ): consumes the 'c' and the next
 *        character, uppercases it and emits it XOR 0x40 (the matching
 *        control character).
 *
 * @note A trailing \c (nothing after the 'c') emits a literal backslash.
 *
 * @param expander Expander state positioned on the 'c' item (borrowed).
 * @param opt Metadata stamped onto the produced item.
 * @return @c ERR_LIBC if the push fails, @c ERR_NO on success.
 */
t_error			dollar_squote_control_escape(
					t_expander *expander,
					t_word_item_opt opt);

/**
 * @ingroup expander_dollar_squote
 * @brief Appends @p c, tagged with @p opt, to the expansion result
 *        @c expander->word_exp.
 *
 * @warning NUL characters are dropped: the function pushes nothing and
 *          returns the current @c expander->err unchanged.
 *
 * @param expander Expander state whose result word is extended (borrowed).
 * @param c Character to emit.
 * @param opt Metadata stamped onto the produced item.
 * @return @c ERR_LIBC if the push fails, @c ERR_NO on success.
 */
t_error			dollar_squote_emit(
					t_expander *expander,
					char c,
					t_word_item_opt opt);

/**
 * @ingroup expander_dollar_squote
 * @brief Rewrites the backslash escape at the word head: consumes the
 *        backslash then routes to the control ( \c ), numeric ( \x or
 *        octal digit) or single-letter handler.
 *
 * An unknown escape re-emits the backslash and the character verbatim; a
 * trailing backslash (end of word) emits a literal backslash.
 *
 * @param expander Expander state positioned on the backslash item
 *                 (borrowed).
 * @param opt Metadata stamped onto the produced items.
 * @param escapes Single-letter escape map built by
 *                @ref dollar_squote_build_map (borrowed, read-only).
 * @return @c ERR_LIBC if a push fails, @c ERR_NO on success.
 */
t_error			dollar_squote_escape(
					t_expander *expander,
					t_word_item_opt opt,
					t_hashmap *escapes);

/**
 * @ingroup expander_dollar_squote
 * @brief Entry point for a $'...' expansion: strips the opening $' (the
 *        '$' may already have been consumed), then rewrites the body,
 *        translating backslash escapes, until the closing quote
 *        (consumed) or the end of the dollar-single-quote context.
 *
 * @note Produced items carry the input item's metadata adjusted by
 *       @ref dollar_squote_result_opt.
 *
 * @param expander Expander state positioned on the '$' item (borrowed).
 * @return @c ERR_LIBC on allocation or push failure; @c ERR_NO on
 *         success (an empty word is caught by assertion).
 */
t_error			dollar_squote_expansion(t_expander *expander);

/**
 * @ingroup expander_dollar_squote
 * @brief Applies a numeric escape: up to three octal digits ( \nnn ) or
 *        'x' followed by up to two hexadecimal digits ( \xHH ); the
 *        decoded value is truncated to one byte and emitted.
 *
 * @note A decoded NUL (a \0 escape, or a digit-less \x ) is dropped by
 *       @ref dollar_squote_emit.
 *
 * @param expander Expander state positioned on the first octal digit or
 *                 on the 'x' item (borrowed).
 * @param opt Metadata stamped onto the produced item.
 * @return @c ERR_LIBC if the
 *         push fails, @c ERR_NO on success.
 */
t_error			dollar_squote_numeric_escape(
					t_expander *expander,
					t_word_item_opt opt);

/**
 * @ingroup expander_dollar_squote
 * @brief Consumes up to @p max leading items of @c expander->word as
 *        base-@p base digits and accumulates them into @p value, stopping
 *        at the first non-digit or at the end of the word.
 *
 * @param expander Expander state whose word is consumed (borrowed).
 * @param base Numeric base of the digits, up to 16.
 * @param max Maximum number of digits to read.
 * @param value Set to the decoded value, zeroed first (borrowed).
 * @return @c ERR_NO, including when no digit was read.
 */
t_error			dollar_squote_read_number(
					t_expander *expander,
					int base,
					size_t max,
					uint *value);

/**
 * @ingroup expander_dollar_squote
 * @brief Derives the metadata of the produced items from the triggering
 *        item's: clears @c context and @c escaped, sets @c is_expand_res.
 *
 * @param in Metadata of the item that triggered the expansion.
 * @return The metadata to stamp onto every produced item.
 */
t_word_item_opt	dollar_squote_result_opt(t_word_item_opt in);

/**
 * @ingroup expander_dollar_squote
 * @brief Tells whether @p current_item starts a $'...' expansion.
 *
 * @param current_item Item at the word head (borrowed, read-only).
 * @param flags Expansion flag bitset.
 * @return @c true when @c EXP_DOLLAR_SQUOTE is active in @p flags and the
 *         item is quoted as @c CONTEXT_DOLLAR_SQUOTE, @c false otherwise.
 */
bool			is_dollar_squote_expansion(
					t_word_item *current_item,
					uint flags);

#endif
