#include "cmd_execute_priv.h"
# include "logs.h"

t_error	exec_builtin(t_cmd *cmd, int *status)
{
	t_error	err;

	fprintf(stderr, MAGENTA "############## BUILTIN %s (START) ##############\n" NC, cmd->name.data);
	err = cmd->entry.data.builtin(cmd->argc, cmd->argv.data, cmd->envp.data, status);
	if (err.type == ERR_BUILTIN)
		err.type = ERR_NO;
	return (err);
}
