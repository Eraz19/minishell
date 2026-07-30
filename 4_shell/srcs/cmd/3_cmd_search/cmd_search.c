#include "cmd.h"
#include "cmd_search_priv.h"

t_error	cmd_search(t_cmd *cmd, bool path_is_temporary)
{
	t_error	err;

	if (cmd->name.len == 0)
		return (error(ERR_POSIX_CMD_NOT_FOUND));
	err = cmd_search_try_absolute_path(&cmd->name, &cmd->entry);
	if (err.type == ERR_POSIX_CMD_NOT_FOUND && path_is_temporary == false)
		err = cmd_search_try_cache(&cmd->name, &cmd->entry);
	if (err.type != ERR_NO && err.type != ERR_LIBC)
		err = cmd_search_try_envp_path(&cmd->name, &cmd->envp, path_is_temporary, &cmd->entry);
	return (err);
}
