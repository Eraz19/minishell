#ifndef CMD_DISPATCHER_H
# define CMD_DISPATCHER_H

# include "error.h"
# include "cmd_type.h"
# include "runner.h"

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @brief Dispatch @p cmd according to its resolved kind.
 *
 * The dispatcher stores the resulting command status into @p cmd->exit_status.
 * Builtins and unspecified commands report their command status through
 * @p cmd->exit_status while still returning @c ERR_NO.
 *
 * @param cmd Resolved command to dispatch (borrowed).
 * @param runner Runner state used for external commands (borrowed).
 * @return @c ERR_NO, @c ERR_NOT_IMPLEMENTED or @c ERR_LIBC.
 */
t_error	cmd_dispatch(t_cmd *cmd, t_runner *runner, int *exit_status);

#endif
