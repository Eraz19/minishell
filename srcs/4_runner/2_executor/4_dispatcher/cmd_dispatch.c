#include "cmd_dispatcher.h"
#include "cmd_dispatcher_priv.h"

static inline void	cmd_exec_builtin(t_cmd *cmd)
{
	int	argc;	// TODO set in cmd_resolve

	argc = (int)cmd->argv.len - 1;
	cmd->exit_status = cmd->builtin(argc, cmd->argv.data, cmd->envp.data);
}

static inline void	cmd_exec_function(t_cmd *cmd)
{
	// TODO: walk_function() ?
	(void)cmd;
	cmd->exit_status = (int)ERR_NOT_IMPLEMENTED;
	(void)error_print(error(ERR_NOT_IMPLEMENTED), "runner", __func__, NULL, NULL);
}

void	cmd_exec_external(t_cmd *cmd)
{
	(void)cmd;
	cmd->exit_status = (int)ERR_NOT_IMPLEMENTED;
	(void)error_print(error(ERR_NOT_IMPLEMENTED), "runner", __func__, NULL, NULL);
}

void	cmd_dispatch(t_cmd *cmd)
{
	if (cmd->type == CMD_NONE || cmd->type == CMD_UNSPECIFIED)
		cmd->exit_status = 0;
	else if (cmd->type == CMD_SPECIAL_BUILTIN || cmd->type == CMD_BUILTIN)
		cmd_exec_builtin(cmd);
	else if (cmd->type == CMD_FUNCTION)
		cmd_exec_function(cmd);
	else
		cmd_exec_external(cmd);
}
