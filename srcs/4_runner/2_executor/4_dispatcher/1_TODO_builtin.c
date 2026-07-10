#include "cmd_dispatcher_priv.h"

t_error	cmd_exec_builtin(t_cmd *cmd)
{
	int	argc;	// TODO set in cmd_resolve

	argc = (int)cmd->argv.len - 1;
	return (cmd->builtin(
					argc,
					cmd->argv.data,
					cmd->envp.data,
					&cmd->exit_status));
}
