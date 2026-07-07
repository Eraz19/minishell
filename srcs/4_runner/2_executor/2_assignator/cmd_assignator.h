#ifndef CMD_ASSIGNATOR_H
# define CMD_ASSIGNATOR_H

# include "error.h"
# include "cmd_resolution_type.h"
# include "tokens.h"

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @brief Apply command assignment words to shell state or to a child
 * environment.
 *
 * For declarations, special builtins and functions, assignments are written to
 * the shell variable store. For other command kinds, assignments are converted
 * into an environment array.
 *
 * @note @p envp is initialized by the function.
 * @note On success, @p envp contains a NUL-terminated array of owned
 *       @c char * items and must be freed with @ref vector_free() using
 *       @ref free_char_ptr_void() as callback.
 *
 * @param cmd_type Resolution kind of the command receiving the assignments.
 * @param assignments Assignment token vector (borrowed, read-only).
 * @param envp Destination vector initialized by the function (borrowed).
 * @return @c ERR_NO, @c ERR_INDEX_OUT_OF_BOUND, @c ERR_SHELL_NOT_FOUND,
 *         @c ERR_VAR_INVALID_NAME, @c ERR_VAR_READ_ONLY,
 *         @c ERR_PARAM_BAD_SUBSTITUTION, @c ERR_PARAM_NULL_OR_UNSET,
 *         @c ERR_NOT_IMPLEMENTED, @c ERR_INCOHERENT_STATE,
 *         @c ERR_QUOTED_TILDE or @c ERR_LIBC.
 */
t_error	cmd_assign(
			t_cmd_type cmd_type,
			const t_tokens *assignments,
			t_vector *envp);

#endif
