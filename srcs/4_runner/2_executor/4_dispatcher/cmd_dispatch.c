#include "cmd_dispatcher.h"
#include "cmd_dispatcher_priv.h"

t_error	cmd_dispatch(t_cmd *cmd, t_runner *runner, int *exit_status)
{
	if (cmd->type == CMD_NONE)
	{
		cmd->exit_status = 0;
		return (error(ERR_NO));
	}
	else if (cmd->type == CMD_SPECIAL_BUILTIN || cmd->type == CMD_BUILTIN)
		return (cmd_exec_builtin(cmd, exit_status));
	else if (cmd->type == CMD_FUNCTION)
		return (cmd_exec_function(cmd, runner, exit_status));
	else
		return (cmd_exec_external(cmd, runner, exit_status));
}
