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
 *  Unimplemented: needs the subshell execution machinery (and, on the
 *  tokenization side, the @c runner_find_cmd_sub_closing stub). The stub
 *  reports @c ERR_NOT_IMPLEMENTED (printed) instead of looping on the
 *  unconsumed construct.
 */

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup expander_cmd_sub
 * @brief Stub: reports the unimplemented command substitution.
 *
 * @param expander Expander state (borrowed).
 * @return @c ERR_NOT_IMPLEMENTED (printed with the function name); the
 *         expander qualifier turns it into @c ERR_INTERNAL.
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
