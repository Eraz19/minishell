/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_cmd_resolve_is_intrinsic_buitlins.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:56:11 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:57:39 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cmd_resolve_priv.h"
#include "builtins.h"

static inline void	cmd_set_intrinsic_builtin(t_cmd *cmd, t_builtin res)
{
	cmd->entry.type = CMD_BUILTIN;
	cmd->entry.data.builtin = res;
}

static inline bool	cmd_name_is_intrinsic_builtin_2(t_cmd *cmd)
{
	if (str_cmp(cmd->name.data, "type") == 0)
		return (cmd_set_intrinsic_builtin(cmd, builtin_type), true);
	else if (str_cmp(cmd->name.data, "ulimit") == 0)
		return (cmd_set_intrinsic_builtin(cmd, builtin_ulimit), true);
	else if (str_cmp(cmd->name.data, "umask") == 0)
		return (cmd_set_intrinsic_builtin(cmd, builtin_umask), true);
	else if (str_cmp(cmd->name.data, "unalias") == 0)
		return (cmd_set_intrinsic_builtin(cmd, builtin_unalias), true);
	else if (str_cmp(cmd->name.data, "wait") == 0)
		return (cmd_set_intrinsic_builtin(cmd, builtin_wait), true);
	return (false);
}

bool	cmd_resolve_is_intrinsic_builtin(t_cmd *cmd)
{
	if (str_cmp(cmd->name.data, "alias") == 0)
		return (cmd_set_intrinsic_builtin(cmd, builtin_alias), true);
	else if (str_cmp(cmd->name.data, "bg") == 0)
		return (cmd_set_intrinsic_builtin(cmd, builtin_bg), true);
	else if (str_cmp(cmd->name.data, "cd") == 0)
		return (cmd_set_intrinsic_builtin(cmd, builtin_cd), true);
	else if (str_cmp(cmd->name.data, "command") == 0)
		return (cmd_set_intrinsic_builtin(cmd, builtin_command), true);
	else if (str_cmp(cmd->name.data, "fc") == 0)
		return (cmd_set_intrinsic_builtin(cmd, builtin_fc), true);
	else if (str_cmp(cmd->name.data, "fg") == 0)
		return (cmd_set_intrinsic_builtin(cmd, builtin_fg), true);
	else if (str_cmp(cmd->name.data, "getopts") == 0)
		return (cmd_set_intrinsic_builtin(cmd, builtin_getopts), true);
	else if (str_cmp(cmd->name.data, "hash") == 0)
		return (cmd_set_intrinsic_builtin(cmd, builtin_hash), true);
	else if (str_cmp(cmd->name.data, "jobs") == 0)
		return (cmd_set_intrinsic_builtin(cmd, builtin_jobs), true);
	else if (str_cmp(cmd->name.data, "kill") == 0)
		return (cmd_set_intrinsic_builtin(cmd, builtin_kill), true);
	else if (str_cmp(cmd->name.data, "read") == 0)
		return (cmd_set_intrinsic_builtin(cmd, builtin_read), true);
	else
		return (cmd_name_is_intrinsic_builtin_2(cmd));
}
