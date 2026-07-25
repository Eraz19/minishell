#include "resolve_priv.h"
#include "params.h"

bool	cmd_resolve_is_function(t_cmd *cmd)
{
	t_error		err;

	err = params_get_function(cmd->name.data, &cmd->entry.data.function);
	if (err.type == ERR_NO)
		cmd->entry.type = CMD_FUNCTION;
	return (err.type == ERR_NO);
}
