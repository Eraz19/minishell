/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_cmd_search_try_envp_path.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:56:38 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:02:03 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_search_priv.h"
#include "env.h"
#include "utils.h"

#define PATH_TARGET				"PATH="
#define PATH_VALUE_START_INDEX	5

// @ret ERR_POSIX_CMD_NOT_FOUND
static inline t_error	cmd_search_find_path_in_envp(
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
		if (assignment_is_same_name(PATH_TARGET, entry))
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

t_error	cmd_search_try_envp_path(
			const t_string *cmd_name,
			const t_vector *envp,
			bool path_is_temporary,
			t_cmd_entry_point *out_entry_point)
{
	t_string			env_path;
	t_cmd_cache			*cmd_cache;
	t_error				err;

	err = cmd_search_find_path_in_envp(envp, &env_path);
	if (err.type)
		return (err);
	err = file_search(
			&env_path, cmd_name, EXECUTABLE, &out_entry_point->data.cmd_path);
	err = cmd_convert_file_error(err);
	if (err.type)
		return (err);
	out_entry_point->type = CMD_EXTERNAL;
	if (path_is_temporary == true)
		return (cmd_search_try_regular_builtin(out_entry_point), err);
	err = env_get_cmd_cache(&cmd_cache);
	if (err.type == ERR_NO)
		err = cmd_cache_set(
				cmd_cache, cmd_name, &out_entry_point->data.cmd_path);
	if (err.type)
		return (out_entry_point->type = CMD_NONE,
			string_free(&out_entry_point->data.cmd_path), err);
	cmd_search_try_regular_builtin(out_entry_point);
	return (err);
}
