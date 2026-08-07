/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:56:50 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 21:28:15 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "cmd_priv.h"
#include "cmd_execute_priv.h"

t_error	cmd_execute(t_cmd *cmd, bool path_is_temporary, int *exit_status)
{
	t_error	err;

	if (cmd->entry.type == CMD_EXTERNAL)
	{
		err = cmd_search(cmd, path_is_temporary);
		if (err.type)
			return (cmd_finalize(cmd, err, exit_status));
	}
	if (cmd->entry.type == CMD_NONE)
	{
		if (exit_status < 0)
			*exit_status = 0;
		return (error(ERR_NO));
	}
	else if (cmd->entry.type == CMD_BUILTIN)
		err = exec_builtin(cmd, exit_status);
	else
		err = exec_external(cmd, exit_status);
	return (cmd_finalize(cmd, err, exit_status));
}
