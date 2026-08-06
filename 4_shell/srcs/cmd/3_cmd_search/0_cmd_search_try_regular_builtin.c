/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_cmd_search_try_regular_builtin.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:56:33 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:56:34 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_search_priv.h"

void	cmd_search_try_regular_builtin(t_cmd_entry_point *out_entry_point)
{
	t_builtin	builtin;

	if (str_cmp(out_entry_point->data.cmd_path.data, "/bin/echo") == 0)
		builtin = builtin_echo;
	else if (str_cmp(out_entry_point->data.cmd_path.data, "/usr/bin/env") == 0)
		builtin = builtin_env;
	else if (str_cmp(out_entry_point->data.cmd_path.data, "/bin/pwd") == 0
		|| str_cmp(out_entry_point->data.cmd_path.data, "/usr/bin/pwd") == 0)
		builtin = builtin_pwd;
	else
		return ;
	out_entry_point->type = CMD_BUILTIN;
	string_free(&out_entry_point->data.cmd_path);
	out_entry_point->data.builtin = builtin;
}
