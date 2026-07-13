#ifndef BACKTICK_SUBSTITUTION__H
# define BACKTICK_SUBSTITUTION__H

# include "expander_.h"

/** @defgroup expander_backtick Backquote substitution
 *  @brief POSIX 2.6.3: backquote-style command substitution.
 *
 *  Unimplemented: needs the subshell execution machinery. The stub
 *  reports @c ERR_NOT_IMPLEMENTED (printed) instead of looping on the
 *  unconsumed construct.
 */

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup expander_backtick
 * @brief Stub: reports the unimplemented backquote substitution.
 *
 * @param expander Expander state (borrowed).
 * @return @c ERR_NOT_IMPLEMENTED (printed with the function name); the
 *         expander qualifier turns it into @c ERR_INTERNAL.
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
