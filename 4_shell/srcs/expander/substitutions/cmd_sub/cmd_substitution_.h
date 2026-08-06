/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_substitution_.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:46:35 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 17:46:36 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_SUBSTITUTION__H
# define CMD_SUBSTITUTION__H

# include "expander_.h"

/** @defgroup expander_cmd_sub Command substitution
 *  @brief POSIX 2.6.3: @c $(...) command substitution.
 *
 *  Runs the construct's pre-parsed AST (recorded at tokenization) in a
 *  subshell and splices the output — trailing newlines trimmed — as
 *  expansion-result items.
 */

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup expander_cmd_sub
 * @brief Substitutes the leading @c $(...) construct of the word with
 *        the output of its pre-parsed AST, run in a subshell; an empty
 *        @c $() is consumed without running anything.
 *
 * @param expander Expander state (borrowed).
 * @return @c ERR_LIBC on allocation, pipe, fork or read failure;
 *         @c ERR_INTERNAL (printed) on an AST index inconsistency;
 *         @c ERR_NO on success.
 */
t_error	cmd_substitution(t_expander *expander);

/**
 * @ingroup expander_cmd_sub
 * @brief Tells whether the current item starts a @c $(...) construct and
 *        @c EXP_CMD_SUB is set.
 *
 * @param current_item Item at the current position (borrowed, read-only).
 * @param flags Active expansion flags.
 */
bool	is_cmd_substitution(t_word_item *current_item, uint flags);

#endif
