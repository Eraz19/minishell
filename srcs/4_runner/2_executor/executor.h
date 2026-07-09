#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "error.h"
# include "runner.h"
# include "ast_type.h"

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @brief Execute one simple command through the executor pipeline.
 *
 * The pipeline resolves words into a @ref t_cmd, applies redirections,
 * processes assignment words, resolves external command paths when needed,
 * dispatches the command and updates the shell last status.
 *
 * @param runner Runner state providing shell services and caches (borrowed).
 * @param simple_command Simple command to execute (borrowed).
 * @return @c ERR_NO, @c ERR_INDEX_OUT_OF_BOUND, @c ERR_REDIRECTION,
 *         @c ERR_OPEN_INVALID_USAGE, @c ERR_INTERRUPTED,
 *         @c ERR_POSIX_CMD_NOT_FOUND, @c ERR_POSIX_CMD_NOT_EXECUTABLE,
 *         @c ERR_SHELL_NOT_FOUND, @c ERR_VAR_INVALID_NAME,
 *         @c ERR_VAR_NOT_FOUND, @c ERR_VAR_READ_ONLY,
 *         @c ERR_PARAM_BAD_SUBSTITUTION, @c ERR_PARAM_NULL_OR_UNSET,
 *         @c ERR_NOT_IMPLEMENTED, @c ERR_INCOHERENT_STATE,
 *         @c ERR_EXP_RESULT_INCOHERENT, @c ERR_QUOTED_TILDE or @c ERR_LIBC.
 */
t_error	cmd_execute(t_runner *runner, t_ast_simple_command *simple_command);

#endif
