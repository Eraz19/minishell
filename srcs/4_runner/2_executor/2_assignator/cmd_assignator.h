#ifndef CMD_ASSIGNATOR_H
# define CMD_ASSIGNATOR_H

# include "error.h"
# include "cmd_type.h"
# include "token.h"

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @brief Apply assignment words to @p cmd and build its execution
 * environment.
 *
 * For @c CMD_NONE, special builtins and functions, assignments are written to
 * the shell variable store. For other command kinds, the function builds
 * @p cmd->envp from the shell environment and merges expanded assignments into
 * it.
 *
 * @note @p cmd must already be initialized by the caller.
 * @note On success, @p cmd->envp contains a NUL-terminated array of owned
 *       @c char * items managed by @ref cmd_free().
 *
 * @param cmd Command receiving the assignments and resulting environment
 *            (borrowed).
 * @param assignments Assignment token vector (borrowed, read-only).
 * @return @c ERR_NO, @c ERR_INDEX_OUT_OF_BOUND, @c ERR_SHELL_NOT_FOUND,
 *         @c ERR_VAR_INVALID_NAME, @c ERR_VAR_READ_ONLY,
 *         @c ERR_VAR_NOT_FOUND,
 *         @c ERR_PARAM_BAD_SUBSTITUTION, @c ERR_PARAM_NULL_OR_UNSET,
 *         @c ERR_NOT_IMPLEMENTED, @c ERR_INCOHERENT_STATE,
 *         @c ERR_QUOTED_TILDE or @c ERR_LIBC.
 */
t_error	cmd_assign(t_cmd *cmd, const t_tokens *assignments);

#endif
