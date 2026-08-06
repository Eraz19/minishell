/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_cmd_resolve_is_special_builtins.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:56:04 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 18:48:32 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cmd_resolve_priv.h"
#include "builtins.h"

static inline void	cmd_set_special_builtin(t_cmd *cmd, t_special_builtin res)
{
	cmd->entry.type = CMD_SPECIAL_BUILTIN;
	cmd->entry.data.special_builtin = res;
}

static inline bool	cmd_resolve_is_special_builtin_2(t_cmd *cmd)
{
	if (str_cmp(cmd->name.data, "shift") == 0)
		return (cmd_set_special_builtin(cmd, builtin_shift), true);
	else if (str_cmp(cmd->name.data, "trap") == 0)
		return (cmd_set_special_builtin(cmd, builtin_trap), true);
	else if (str_cmp(cmd->name.data, "unset") == 0)
		return (cmd_set_special_builtin(cmd, builtin_unset), true);
	return (false);
}

bool	cmd_resolve_is_special_builtin(t_cmd *cmd)
{
	if (str_cmp(cmd->name.data, "break") == 0)
		return (cmd_set_special_builtin(cmd, builtin_break), true);
	else if (str_cmp(cmd->name.data, ":") == 0)
		return (cmd_set_special_builtin(cmd, builtin_colon), true);
	else if (str_cmp(cmd->name.data, "continue") == 0)
		return (cmd_set_special_builtin(cmd, builtin_continue), true);
	else if (str_cmp(cmd->name.data, ".") == 0)
		return (cmd_set_special_builtin(cmd, builtin_dot), true);
	else if (str_cmp(cmd->name.data, "eval") == 0)
		return (cmd_set_special_builtin(cmd, builtin_eval), true);
	else if (str_cmp(cmd->name.data, "exit") == 0)
		return (cmd_set_special_builtin(cmd, builtin_exit), true);
	else if (str_cmp(cmd->name.data, "export") == 0)
		return (cmd_set_special_builtin(cmd, builtin_export), true);
	else if (str_cmp(cmd->name.data, "readonly") == 0)
		return (cmd_set_special_builtin(cmd, builtin_readonly), true);
	else if (str_cmp(cmd->name.data, "return") == 0)
		return (cmd_set_special_builtin(cmd, builtin_return), true);
	else if (str_cmp(cmd->name.data, "set") == 0)
		return (cmd_set_special_builtin(cmd, builtin_set), true);
	else
		return (cmd_resolve_is_special_builtin_2(cmd));
}
