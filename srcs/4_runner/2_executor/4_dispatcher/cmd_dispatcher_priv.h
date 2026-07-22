#ifndef CMD_DISPATCHER_PRIV_H
# define CMD_DISPATCHER_PRIV_H

# include "error.h"
# include "cmd_type.h"
# include "runner_type.h"

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

// TODO: doc
t_error	cmd_exec_builtin(t_cmd *cmd, t_runner *runner);

/**
 * @brief Execute an external command in a child process.
 *
 * The child first tries @c execve() on @p cmd->path. When that fails with
 * @c ENOEXEC, it re-enters the shell through @ref shell_run() after rebuilding
 * @p cmd->argv. The resulting child exit status or terminating signal is stored
 * into @p cmd->exit_status.
 *
 * @param cmd External command descriptor with a resolved path (borrowed).
 * @param runner Runner state used for redirection cleanup in the child
 *               (borrowed).
 * @return @c ERR_NO on successful child completion, @c ERR_INTERRUPTED when the
 *         parent wait loop is interrupted and must stop, or @c ERR_LIBC on
 *         @c fork() / @c waitpid() failure.
 */
t_error	cmd_exec_external(t_cmd *cmd);

/**
 * @brief Execute a shell function already selected in @p cmd.
 *
 * @warning The current implementation is a stub and returns
 *          @c ERR_NOT_IMPLEMENTED.
 *
 * @param cmd Function command descriptor (borrowed).
 * @return @c ERR_NOT_IMPLEMENTED.
 */
t_error	cmd_exec_function(t_cmd *cmd, t_runner *runner);

#endif
