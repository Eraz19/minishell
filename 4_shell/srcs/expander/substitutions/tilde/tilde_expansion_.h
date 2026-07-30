#ifndef TILDE_EXPANSION__H
# define TILDE_EXPANSION__H

#include "expander_.h"

/** @defgroup expander_tilde Tilde expansion
 *  @brief POSIX 2.6.1: replaces an unquoted tilde prefix with the home
 *         directory of the current or named user.
 */

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup expander_tilde
 * @brief Replaces the tilde prefix with the resolved home directory, or
 *        keeps it literal when any character of the prefix is quoted
 *        (@c ERR_QUOTED_TILDE is consumed here, never escapes), when the
 *        user is unknown, or when @c HOME is unset for a bare tilde.
 *
 * @param expander Expander state (borrowed).
 * @return @c ERR_LIBC on allocation failure; @c ERR_INTERRUPTED when a
 *         signal interrupts the password-file lookup;
 *         @c ERR_SHELL_NOT_FOUND if the shell parameters are
 *         unavailable; @c ERR_EMPTY_STACK or @c ERR_INDEX_OUT_OF_BOUND
 *         on a word inconsistency; @c ERR_NO on success.
 */
t_error	expand_user_path(t_expander *expander);

/**
 * @ingroup expander_tilde
 * @brief Tells whether the current position starts a tilde expansion:
 *        an unquoted tilde at the start of the word
 *        (@c EXP_TILDE_NORMAL), or right after the @c '=' of an
 *        assignment value (@c EXP_TILDE_ASSIGNMENT).
 *
 * @param expander Expander state (borrowed, read-only).
 * @param current_item Item at the current position (borrowed, read-only).
 */
bool	is_tilde_expansion(t_expander *expander, t_word_item *current_item);

/**
 * @ingroup expander_tilde
 * @brief Entry point of the tilde substitution, dispatching to
 *        @ref expand_user_path.
 *
 * @param expander Expander state (borrowed).
 * @return Same contract as @ref expand_user_path.
 */
t_error	tilde_expansion(t_expander *expander);

#endif
