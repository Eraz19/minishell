#include "cmd_searcher_priv.h"
#include "entry_is_target.h"
#include "cmd_type.h"

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

// @ret ERR_LIBC
static inline t_error	cmd_build_path(t_cmd *cmd, const t_string *path_entry)
{
	cmd->path.len = 0;
	if (path_entry->len == 0)
	{
		if (!string_append_n(&cmd->path, "./", 2))
			return (error_sys());
	}
	else
	{
		if (!string_append(&cmd->path, path_entry))
			return (error_sys());
		if (path_entry->data[path_entry->len - 1] != '/'
			&& !string_append_n(&cmd->path, "/", 1))
				return (error_sys());
	}
	if (!string_append(&cmd->path, &cmd->name))
		return (error_sys());
	return (error(ERR_NO));
}

// @ret ERR_POSIX_CMD_NOT_EXECUTABLE / ERR_POSIX_CMD_NOT_FOUND / ERR_LIBC
static inline t_error	cmd_find(t_cmd *cmd, t_vector *path_entries)
{
	size_t			i;
	bool			found;
	const t_string	*entry;
	t_error			err;

	found = false;
	i = 0;
	while (i < path_entries->len)
	{
		entry = &((t_string *)path_entries->data)[i++];
		err = cmd_build_path(cmd, entry);
		if (err.type)
			return (string_free(&cmd->path), err);
		err = cmd_check(&cmd->path, &found);
		if (err.type == ERR_NO)
			return (cmd_try_regular_builtin(cmd), err);
		string_free(&cmd->path);
		if (err.type == ERR_LIBC)
			return (err);
	}
	if (found == true)
		return (error(ERR_POSIX_CMD_NOT_EXECUTABLE));
	return (error(ERR_POSIX_CMD_NOT_FOUND));
}

t_error	cmd_try_envp_path(t_cmd *cmd, t_cmd_cache *cache)
{
	t_string	path;
	t_vector	path_entries;
	t_error		err;

	err = cmd_find_path_in_envp(&cmd->envp, &path);
	if (err.type)
		return (err);
	if (!string_split_on_char(&path, ':', true, &path_entries))
		return (error_sys());
	err = cmd_find(cmd, &path_entries);
	vector_free(&path_entries, string_free_void);
	if (err.type == ERR_NO && cmd->type == CMD_EXTERNAL && cache != NULL)
		err = cmd_cache_set(cache, &cmd->name, &cmd->path);
	return (err);
}
