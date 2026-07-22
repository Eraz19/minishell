#include "cmd_dispatcher_priv.h"

# include <stdio.h>	// DEBUG
t_error	cmd_exec_builtin(t_cmd *cmd, t_runner *runner)
{
	int		argc;
	t_error	err;

	argc = (int)cmd->argv.len - 1;
	if (cmd->type != CMD_SPECIAL_BUILTIN)
		err = cmd->builtin(argc, cmd->argv.data, cmd->envp.data, &cmd->exit_status);
	else
		err = cmd->special_builtin(argc, cmd->argv.data, runner, &cmd->exit_status);
	if (err.type == ERR_BUILTIN)
	{
		if (cmd->type == CMD_SPECIAL_BUILTIN)
			err.type = ERR_POSIX_BUILTIN_SPECIAL;
		else
			err.type = ERR_NO;
	}
	return (err);
}
