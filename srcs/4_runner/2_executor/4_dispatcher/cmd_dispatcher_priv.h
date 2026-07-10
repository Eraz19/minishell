#ifndef CMD_DISPATCHER_PRIV_H
# define CMD_DISPATCHER_PRIV_H

# include "error.h"
# include "cmd_type.h"
# include "runner.h"

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @brief Execute the builtin already selected in @p cmd.
 *
 * The dispatcher derives @c argc from the NULL-terminated @p cmd->argv, then
 * forwards @p cmd->argv, @p cmd->envp and @p cmd->exit_status to
 * @p cmd->builtin.
 *
 * @param cmd Builtin command descriptor updated in place (borrowed).
 * @return The requalified error code returned by @p cmd->builtin() ( @c ERR_NO
 *			@c ERR_POSIX_BUILTIN_SPECIAL @c ERR_INTERRUPTED @c ERR_INTERNAL
 *			or @c ERR_LIBC ).
 */
t_error	cmd_exec_builtin(t_cmd *cmd);

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
