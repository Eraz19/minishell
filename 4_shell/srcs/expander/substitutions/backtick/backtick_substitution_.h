/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtick_substitution_.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:46:27 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 17:46:28 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BACKTICK_SUBSTITUTION__H
# define BACKTICK_SUBSTITUTION__H

# include "expander_.h"

/** @defgroup expander_backtick Backquote substitution
 *  @brief POSIX 2.6.3: backquote-style command substitution.
 *
 *  Extracts the command between the backquotes (removing the backslash
 *  of the @c \$ @c \` @c \\ pairs per 2.6.3), runs it in a subshell and
 *  splices the output (trailing newlines trimmed) as expansion-result
 *  items.
 */

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup expander_backtick
 * @brief Substitutes the leading backquote construct of the word with
 *        the output of its command, run in a subshell.
 *
 * @param expander Expander state (borrowed).
 * @return @c ERR_LIBC on allocation, pipe, fork or read failure;
 *         @c ERR_NO on success (span inconsistencies are caught by
 *         assertion).
 */
t_error	backtick_substitution(t_expander *expander);

/**
 * @ingroup expander_backtick
 * @brief Tells whether the current item starts a backquote construct and
 *        @c EXP_CMD_SUB is set.
 *
 * @param current_item Item at the current position (borrowed, read-only).
 * @param flags Active expansion flags.
 */
bool	is_backtick_substitution(t_word_item *current_item, uint flags);

#endif
