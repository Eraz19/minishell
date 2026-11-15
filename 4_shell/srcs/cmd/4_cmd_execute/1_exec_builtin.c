/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_exec_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:56:44 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 21:27:25 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_execute_priv.h"

t_error	exec_builtin(t_cmd *cmd, int *status)
{
	t_error	err;

	err = cmd->entry.data.builtin(
			cmd->argc, cmd->argv.data, cmd->envp.data, status);
	if (err.type == ERR_BUILTIN)
		err.type = ERR_NO;
	return (err);
}
