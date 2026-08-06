/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_walk_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:23:43 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:30:32 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "walker.h"
#include "walker_priv.h"
#include "env.h"
#include "redirector.h"
#include "debug.h"
#include <assert.h>

static inline t_error	walk_command_dispatch(
							t_runner *runner,
							t_ast_command *command,
							int *exit_status)
{
	t_error	err;

	assert((command->type != AST_CMD_SIMPLE && command->type != AST_CMD_FUNCTION_DEF) || command->redirs.len == 0);
	if (command->type == AST_CMD_SIMPLE)
		return (walk_simple_cmd(runner, &command->data.simple, exit_status));
	else if (command->type == AST_CMD_LIST)
		return (walk_list(runner, &command->data.list, exit_status));
	else if (command->type == AST_CMD_IF)
		return (walk_if(runner, &command->data.if_clause, exit_status));
	else if (command->type == AST_CMD_FOR)
		return (walk_for(runner, &command->data.for_clause, exit_status));
	else if (command->type == AST_CMD_LOOP)
		return (walk_loop(runner, &command->data.loop, exit_status));
	else if (command->type == AST_CMD_CASE)
		return (walk_case(runner, &command->data.case_clause, exit_status));
	else if (command->type == AST_CMD_FUNCTION_DEF)
	{
		err = env_set_function(&command->data.function_def);
		if (err.type == ERR_NO)
			*exit_status = 0;
		return (err);
	}
	return (error_print(error(ERR_NOT_IMPLEMENTED), "walker", NULL,
			"command type %s", ast_command_type_to_string(command->type)));
}

t_error	walk_command(t_runner *runner, t_ast_command *command, int *exit_status)
{
	t_error	err;

	err = redirect_start(&command->redirs, exit_status);
	if (err.type)
		return (err);
	err = walk_command_dispatch(runner, command, exit_status);
	return (error_priorize(err, redirect_stop()));
}
