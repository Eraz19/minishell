/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_exec_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:56:44 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:03:31 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_execute_priv.h"
#ifdef DEBUG_CMD
# include "logs.h"
#endif

t_error	exec_builtin(t_cmd *cmd, int *status)
{
	t_error	err;

#ifdef DEBUG_CMD
	fprintf(stderr, MAGENTA "############## BUILTIN %s (START) ##############\n" NC, cmd->name.data);
#endif
	err = cmd->entry.data.builtin(
			cmd->argc, cmd->argv.data, cmd->envp.data, status);
	if (err.type == ERR_BUILTIN)
		err.type = ERR_NO;
	return (err);
}
