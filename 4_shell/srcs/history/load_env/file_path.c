/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:09:01 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/05 19:04:36 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "debug.h"
#include "history_load_env.h"
#include "history_load_env_priv.h"

bool	load_file_path(t_history *history, const char *var_name)
{
	history->err = env_get_from_const(var_name, &history->file.path);
	if (history->err.type || history->file.path.len <= 0)
		return (string_free(&history->file.path), false);
	history_load_file_path_from_logs(history->file.path.data, var_name);
	return (true);
}

t_error	load_history_path_from_env(t_history *history)
{
	if (load_file_path(history, "HISTFILE"))
		return (history->err);
	if (history->err.type && history->err.type != ERR_VAR_NOT_FOUND)
		return (history->err);
	if (load_file_path(history, "HOME"))
	{
		if (!string_append_n(&history->file.path, "/.sh_history", -1))
			return (history->err = error_sys());
		return (history->err);
	}
	if (history->err.type && history->err.type != ERR_VAR_NOT_FOUND)
		return (history->err);
	on_history_disabled_error();
	return (history->err = error(ERR_NO));
}
