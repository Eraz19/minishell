#include "cmd_searcher_priv.h"
#include "entry_is_target.h"

#define PATH_TARGET				"PATH="
#define PATH_VALUE_START_INDEX	5

// @ret ERR_POSIX_CMD_NOT_FOUND
static inline t_error	cmd_find_path_in_envp(
							const t_vector *envp,
							t_string *ref_path)
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
			ref_path->data = entry + PATH_VALUE_START_INDEX;
			ref_path->cap = 0;
			ref_path->len = str_len(ref_path->data);
			return (error(ERR_NO));
		}
		i++;
	}
	return (error(ERR_POSIX_CMD_NOT_FOUND));
}

// @ret ERR_LIBC
static inline t_error	cmd_build_path(
							const t_string *cmd_name,
							const t_string *path_entry,
							t_string *out_cmd_path)
{
	out_cmd_path->len = 0;
	if (path_entry->len == 0)
	{
		if (!string_append_n(out_cmd_path, "./", 2))
			return (error_sys());
	}
	else
	{
		if (!string_append(out_cmd_path, path_entry))
			return (error_sys());
		if (path_entry->data[path_entry->len - 1] != '/'
			&& !string_append_n(out_cmd_path, "/", 1))
				return (error_sys());
	}
	if (!string_append(out_cmd_path, cmd_name))
		return (error_sys());
	return (error(ERR_NO));
}

// @ret ERR_POSIX_CMD_NOT_EXECUTABLE / ERR_POSIX_CMD_NOT_FOUND / ERR_LIBC
static inline t_error	cmd_find(
							const t_string *cmd_name,
							t_vector *path_entries,
							t_string *ref_cmd_path)
{
	bool			is_valid;
	bool			found_but_not_executable;
	const t_string	*entry;
	size_t			i;
	t_error			err;

	found_but_not_executable = false;
	i = 0;
	while (i < path_entries->len)
	{
		entry = &((t_string *)path_entries->data)[i];
		err = cmd_build_path(cmd_name, entry, ref_cmd_path);
		if (err.type)
			return (string_free(ref_cmd_path), err);
		err = cmd_check(ref_cmd_path, &is_valid, &found_but_not_executable);
		if (err.type)
			return (string_free(ref_cmd_path), err);
		else if (is_valid == true)
			return (err);
		i++;
	}
	string_free(ref_cmd_path);
	if (found_but_not_executable == true)
		return (error(ERR_POSIX_CMD_NOT_EXECUTABLE));
	return (error(ERR_POSIX_CMD_NOT_FOUND));
}

t_error	cmd_try_envp_path(
			const t_string *cmd_name,
			t_cmd_cache	*cache,
			const t_vector *envp,
			t_string *ref_cmd_path)
{
	t_string	path;
	t_vector	path_entries;
	t_error		err;

	err = cmd_find_path_in_envp(envp, &path);
	if (err.type)
		return (err);
	if (!string_split_on_char(&path, ':', true, &path_entries))
		return (error_sys());
	err = cmd_find(cmd_name, &path_entries, ref_cmd_path);
	vector_free(&path_entries, string_free_void);
	if (err.type == ERR_NO && cache != NULL)
		err = cmd_cache_set(cache, cmd_name, ref_cmd_path);
	return (err);
}
