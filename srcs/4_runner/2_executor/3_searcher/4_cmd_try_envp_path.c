#include "cmd_searcher_priv.h"
#include "entry_is_target.h"
#include "cmd_type.h"
#include "utils.h"

#define PATH_TARGET				"PATH="
#define PATH_VALUE_START_INDEX	5

// @ret ERR_POSIX_CMD_NOT_FOUND
static inline t_error	cmd_find_path_in_envp(
							const t_vector *envp,
							t_string *out_path)
{
	char	*entry;
	size_t	i;

	i = 0;
	while (i < envp->len)
	{
		entry = ((char **)envp->data)[i];
		if (entry == NULL)
			break ;
		if (cmd_entry_is_target(PATH_TARGET, entry))
		{
			if (entry[PATH_VALUE_START_INDEX] == '\0')
				return (error(ERR_POSIX_CMD_NOT_FOUND));
			out_path->data = entry + PATH_VALUE_START_INDEX;
			out_path->cap = 0;
			out_path->len = str_len(out_path->data);
			return (error(ERR_NO));
		}
		i++;
	}
	return (error(ERR_POSIX_CMD_NOT_FOUND));
}

t_error	cmd_try_envp_path(t_cmd *cmd, t_cmd_cache *cache)
{
	t_string	path;
	t_error		err;

	err = cmd_find_path_in_envp(&cmd->envp, &path);
	if (err.type)
		return (err);
	err = search_file(&path, &cmd->name, SEARCH_FILE_EXEC, &cmd->path);
	if (err.type == ERR_NO)
	{
		cmd_try_regular_builtin(cmd);
		if (cmd->type == CMD_EXTERNAL && cache != NULL)
			err = cmd_cache_set(cache, &cmd->name, &cmd->path);
	}
	else if (err.type == ERR_FILE_NOT_FOUND)
		err.type = ERR_POSIX_CMD_NOT_FOUND;
	else if (err.type == ERR_FILE_NOT_EXECUTABLE)
		err.type = ERR_POSIX_CMD_NOT_EXECUTABLE;
	return (err);
}
