#ifndef CMD_DISPATCHER_PRIV_H
# define CMD_DISPATCHER_PRIV_H

# include "error.h"
# include "cmd_type.h"
# include "runner.h"

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @brief Execute a builtin already selected in @p cmd.
 *
 * The builtin return value is stored into @p cmd->exit_status.
 *
 * @param cmd Builtin command descriptor (borrowed).
 * @return @c ERR_NO.
 */
t_error	cmd_exec_builtin(t_cmd *cmd);

/**
 * @brief Execute an external command in a child process.
 *
 * The child exit status or terminating signal is stored into
 * @p cmd->exit_status.
 *
 * @param cmd External command descriptor with a resolved path (borrowed).
 * @param runner Runner state used for redirection cleanup in the child
 *               (borrowed).
 * @return @c ERR_NO or @c ERR_LIBC.
 */
t_error	cmd_exec_external(t_cmd *cmd, t_runner *runner);

/**
 * @brief Execute a shell function already selected in @p cmd.
 *
 * @warning The current implementation is a stub and returns
 *          @c ERR_NOT_IMPLEMENTED.
 *
 * @param cmd Function command descriptor (borrowed).
 * @return @c ERR_NOT_IMPLEMENTED.
 */
t_error	cmd_exec_function(t_cmd *cmd);

#endif
