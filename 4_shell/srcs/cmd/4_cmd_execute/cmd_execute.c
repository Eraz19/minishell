#include "cmd.h"
#include "cmd_priv.h"
#include "cmd_execute_priv.h"
# include <assert.h>
#ifdef DEBUG_CMD
# include "logs.h"
#endif

t_error	cmd_execute(t_cmd *cmd, bool path_is_temporary, int *exit_status)
{
	t_error	err;

	assert(cmd->entry.type == CMD_NONE || cmd->entry.type == CMD_EXTERNAL || cmd->entry.type == CMD_BUILTIN);
	if (cmd->entry.type == CMD_EXTERNAL)
	{
		err = cmd_search(cmd, path_is_temporary);
		if (err.type)
		{
#ifdef DEBUG_CMD
			fprintf(stderr, MAGENTA "############## EXTERNAL %s (START) ##############\n" NC, cmd->name.data);
#endif
			return (cmd_finalize(cmd, err, exit_status));
		}
	}
	if (cmd->entry.type == CMD_NONE)
	{
#ifdef DEBUG_CMD
		fprintf(stderr, MAGENTA "############## %s (START) ##############\n" NC, cmd->name.data);
#endif
		*exit_status = 0;
		return (error(ERR_NO));
	}
	else if (cmd->entry.type == CMD_BUILTIN)
		err = exec_builtin(cmd, exit_status);
	else
		err = exec_external(cmd, exit_status);
	return (cmd_finalize(cmd, err, exit_status));
}
