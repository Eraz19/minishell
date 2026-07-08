#include "cmd_dispatcher_priv.h"

t_error	cmd_exec_function(t_cmd *cmd)
{
	// TODO: walk_function() ?
	(void)cmd;
	cmd->exit_status = (int)ERR_NOT_IMPLEMENTED;
	return (error_print(error(ERR_NOT_IMPLEMENTED), "runner", __func__, NULL, NULL));
}
