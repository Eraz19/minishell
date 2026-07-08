#include "cmd_searcher.h"
#include "cmd_searcher_priv.h"
#include "cmd_cache.h"

t_error	cmd_search(t_cmd *cmd, t_cmd_cache *cache)
{
	bool	found;
	t_error	err;

	(void)string_init(&cmd->path, 0, NULL, 0);
	found = false;
	if (cmd->name.len == 0)
		err = error(ERR_POSIX_CMD_NOT_FOUND);
	else
	{
		err = cmd_try_absolute_path(&cmd->name, &cmd->path);
		if (err.type == ERR_POSIX_CMD_NOT_FOUND)
			err = cmd_try_cache(&cmd->name, cache, &found, &cmd->path);
		if (err.type == ERR_POSIX_CMD_NOT_FOUND || err.type == ERR_POSIX_CMD_NOT_EXECUTABLE)
		{
			err = cmd_try_envp_path(&cmd->name, cache, &cmd->envp, &cmd->path);
			if (err.type == ERR_POSIX_CMD_NOT_FOUND && found == true)
				err = error(ERR_POSIX_CMD_NOT_EXECUTABLE);
		}
	}
	if (err.type == ERR_POSIX_CMD_NOT_FOUND || err.type == ERR_POSIX_CMD_NOT_EXECUTABLE)
		err = error_print(err, "runner", NULL, "%s", cmd->name.data);
	return (err);
}
