#include "libft.h"
#include "error.h"
#include "cmd_searcher_priv.h"
#include "cmd_type.h"

t_error	cmd_try_cache(t_cmd *cmd, t_cmd_cache *cache)
{
	const t_string	*cmd_path_from_cache;
	bool			found;
	t_error			err;

	if (cache == NULL)
		return (error(ERR_POSIX_CMD_NOT_FOUND));
	err = cmd_cache_get(cache, &cmd->name, &cmd_path_from_cache);
	if (err.type)
		return (err);
	err = cmd_check(cmd_path_from_cache, &found);
	if (err.type == ERR_POSIX_CMD_NOT_FOUND
		|| err.type == ERR_POSIX_CMD_NOT_EXECUTABLE)
		cmd_cache_unset(cache, &cmd->name);
	if (err.type)
		return (err);
	if (!string_dup(&cmd->path, cmd_path_from_cache))
		return (error_sys());
	cmd_try_regular_builtin(cmd);
	return (err);
}
