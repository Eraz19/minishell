/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_cmd_life_cycle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:56:52 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:56:53 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "utils.h"

void	cmd_init(t_cmd *cmd)
{
	cmd->entry = (t_cmd_entry_point){0};
	(void)string_init(&cmd->name, 0, NULL, 0);
	cmd->argc = 0;
	(void)vector_init(&cmd->argv, sizeof(char *), 0);
	(void)vector_init(&cmd->envp, sizeof(char *), 0);
}

void	cmd_free(t_cmd *cmd)
{
	if (cmd->entry.type == CMD_EXTERNAL)
		string_free(&cmd->entry.data.cmd_path);
	cmd->entry.type = CMD_NONE;
	cmd->entry = (t_cmd_entry_point){0};
	string_free(&cmd->name);
	cmd->argc = 0;
	vector_free(&cmd->argv, free_char_ptr_void);
	vector_free(&cmd->envp, free_char_ptr_void);
}
