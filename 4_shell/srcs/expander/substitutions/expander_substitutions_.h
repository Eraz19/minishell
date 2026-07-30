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
 *         @c ERR_PARAM_BAD_SUBSTITUTION, @c ERR_PARAM_NULL_OR_UNSET,
 *         @c ERR_VAR_INVALID_NAME, @c ERR_VAR_READ_ONLY,
 *         @c ERR_NOT_IMPLEMENTED (printed) from the command, backquote
 *         and arithmetic stubs, @c ERR_INCOHERENT_STATE,
 *         @c ERR_EMPTY_STACK, @c ERR_INDEX_OUT_OF_BOUND,
 *         @c ERR_SHELL_NOT_FOUND); @c ERR_NO on success.
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
