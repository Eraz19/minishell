/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_substitutions_.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:48:12 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 17:48:13 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_SUBSTITUTIONS__H
# define EXPANDER_SUBSTITUTIONS__H

# include "error.h"
# include "expander_.h"

/** @defgroup expander_substitutions Expander substitutions
 *  @brief First pipeline stage: rewrites every construct of every field
 *         (tilde, ANSI-C quoting, parameter, command, backquote and
 *         arithmetic), left to right (POSIX 2.6 step 1).
 */

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup expander_substitutions
 * @brief Handles one position of the current word: dispatches to the
 *        matching substitution when a construct starts here (and its
 *        flag is set), otherwise forwards the character unchanged.
 *
 * @note Characters tagged @c is_expand_res are never rescanned.
 * @param expander Expander state (borrowed).
 * @return The dispatched substitution's error, raw (@c ERR_LIBC,
 *         @c ERR_POSIX_EXPANSION and @c ERR_POSIX_ASSIGNMENT (printed
 *         and requalified at production), @c ERR_INTERNAL (printed;
 *         arithmetic stub and env instance lookups) and @c ERR_LIBC);
 *         @c ERR_NO on success.
 */
t_error	substitution_char(t_expander *expander);

/**
 * @ingroup expander_substitutions
 * @brief Runs the substitution stage on every field, replacing the
 *        expander's fields with the rewritten ones.
 *
 * @param expander Expander state (borrowed).
 * @return Same raw error surface as @ref substitution_char; @c ERR_NO on
 *         success.
 */
t_error	substitutions(t_expander *expander);

#endif
