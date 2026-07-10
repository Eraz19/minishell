#include "cmd_dispatcher_priv.h"

t_error	cmd_exec_builtin(t_cmd *cmd)
{
	int		argc;
	t_error	err;

	argc = (int)cmd->argv.len - 1;
	err = cmd->builtin(argc, cmd->argv.data, cmd->envp.data, &cmd->exit_status);
	if (err.type == ERR_BUILTIN)
	{
		if (cmd->type == CMD_SPECIAL_BUILTIN)
			err.type = ERR_POSIX_BUILTIN_SPECIAL;
		else
			err.type = ERR_NO;
	}
	return (err);
}
