/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_splitting_.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:43:51 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 17:43:52 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIELD_SPLITTING__H
# define FIELD_SPLITTING__H

# include "expander_.h"

/** @defgroup expander_field_splitting Expander field splitting
 *  @brief POSIX 2.6.5 field splitting: cuts each field on the resolved
 *         IFS (see @ref get_ifs), using only unquoted expansion-result
 *         characters as delimiters (literal text is never split).
 *
 *  A run of IFS whitespace is one delimiter; a non-whitespace IFS
 *  character delimits on its own (an empty field between two of them is
 *  kept). A quoted empty word stays one field, an unquoted expansion
 *  producing nothing yields no field.
 *
 *  @note Every @ref t_error function also records its result in
 *        @c expander->err before returning it.
 */

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup expander_field_splitting
 * @brief Keeps @p item: appends it to @c expander->word_exp and pops the
 *        head of @c expander->word.
 *
 * @warning @p item must be the head of @c expander->word (peeked with
 *          @ref word_get): the head is popped and discarded without
 *          comparing it to @p item.
 * @param expander Expander state (borrowed).
 * @param item Item to keep (copied by value).
 * @return @c ERR_LIBC if the push fails, @c ERR_NO on success (an
 *         empty word is caught by assertion).
 */
t_error	consume_word_item(t_expander *expander, t_word_item item);

/**
 * @ingroup expander_field_splitting
 * @brief Closes the field under construction: pushes
 *        @c expander->word_exp into @c expander->fields_exp and
 *        re-initializes @c word_exp.
 *
 * @note An empty @c word_exp yields an empty field.
 * @warning On failure @c word_exp is left as is, still owned by the
 *          expander.
 * @param expander Expander state (borrowed).
 * @return @c ERR_LIBC if the push fails, @c ERR_NO on success.
 */
t_error	delim_field(t_expander *expander);

/**
 * @ingroup expander_field_splitting
 * @brief Splits every field of @c state->fields on @c state->ifs and
 *        replaces the container with the produced fields.
 *
 * @note On failure the fields produced so far are freed and the
 *       remaining input stays in @c state->fields for
 *       @ref expander_free.
 * @param state Loaded expander state (borrowed).
 * @return @c ERR_LIBC if a push fails, @c ERR_NO on success.
 */
t_error	field_splitting(t_expander *state);

/**
 * @ingroup expander_field_splitting
 * @brief Handles a non-whitespace IFS delimiter at the head of
 *        @c expander->word: closes the current field (even empty), pops
 *        the delimiter, then consumes any adjacent IFS whitespace.
 *
 * @param expander Expander state (borrowed).
 * @return @c ERR_LIBC if a push fails, @c ERR_NO on success (an empty
 *         word is caught by assertion).
 */
t_error	fields_splitting_on_ifs_non_white_space(t_expander *expander);

/**
 * @ingroup expander_field_splitting
 * @brief Handles an IFS whitespace delimiter: consumes the whole run of
 *        IFS-whitespace delimiters at the head of @c expander->word,
 *        then closes the current field when it is not empty and a
 *        non-delimiter follows.
 *
 * @note Closing is deferred to
 *       @ref fields_splitting_on_ifs_non_white_space when the run is
 *       followed by a non-whitespace delimiter, so the pair counts as
 *       one delimiter.
 * @param expander Expander state (borrowed).
 * @return @c ERR_LIBC if a push fails, @c ERR_NO on success.
 */
t_error	fields_splitting_on_ifs_white_space(t_expander *expander);

/**
 * @ingroup expander_field_splitting
 * @brief Tells whether @p item delimits fields: an unquoted
 *        expansion-result item (@c is_expand_res) whose character
 *        appears in @p ifs.
 *
 * @param item Item to classify.
 * @param ifs Resolved field separators (borrowed, read-only).
 */
bool	is_delim(t_word_item item, const t_string *ifs);

/**
 * @ingroup expander_field_splitting
 * @brief Tells whether @p c is IFS whitespace: space, tab or newline.
 *
 * @note Pure character test: callers combine it with @ref is_delim to
 *       check membership in the actual IFS.
 * @param c Character to test.
 */
bool	is_it_white_space_ifs(char c);

#endif
