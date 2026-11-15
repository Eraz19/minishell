/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_cmd_resolve_is_function.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:56:09 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:57:39 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_resolve_priv.h"
#include "env.h"

bool	cmd_resolve_is_function(t_cmd *cmd)
{
	t_error		err;

	err = env_get_function(cmd->name.data, &cmd->entry.data.function);
	if (err.type == ERR_NO)
		cmd->entry.type = CMD_FUNCTION;
	return (err.type == ERR_NO);
}
