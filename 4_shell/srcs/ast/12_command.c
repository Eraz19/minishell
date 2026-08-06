/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:35:38 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:39:42 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "debug.h"
#include <assert.h>	// DEBUG

void	ast_command_init(t_ast_command *command)
{
	assert(command != NULL);
	command->type = AST_CMD_TYPE_COUNT;
	ast_redir_list_init(&command->redirs);
	command->data = (t_ast_command_data){0};
}

static inline t_error	ast_command_dup_data(
							t_ast_command *dst,
							const t_ast_command *src)
{
	if (src->type == AST_CMD_SIMPLE)
		return (ast_simple_command_dup(&dst->data.simple, &src->data.simple));
	else if (src->type == AST_CMD_LIST)
		return (ast_list_dup(&dst->data.list, &src->data.list));
	else if (src->type == AST_CMD_IF)
		return (ast_if_dup(&dst->data.if_clause, &src->data.if_clause));
	else if (src->type == AST_CMD_FOR)
		return (ast_for_dup(&dst->data.for_clause, &src->data.for_clause));
	else if (src->type == AST_CMD_LOOP)
		return (ast_loop_dup(&dst->data.loop, &src->data.loop));
	else if (src->type == AST_CMD_CASE)
		return (ast_case_dup(&dst->data.case_clause, &src->data.case_clause));
	else if (src->type == AST_CMD_FUNCTION_DEF)
		return (ast_function_def_dup(&dst->data.function_def,
				&src->data.function_def));
	return (error_print(error(ERR_INTERNAL), "unknown command type",
			NULL, "%s", ast_command_type_to_string(src->type)));
}

t_error	ast_command_dup(void *dst, const void *src)
{
	t_ast_command		*dst_command;
	const t_ast_command	*src_command;
	t_error				err;

	dst_command = (t_ast_command *)dst;
	src_command = (const t_ast_command *)src;
	ast_command_init(dst_command);
	dst_command->type = src_command->type;
	err = ast_command_dup_data(dst_command, src_command);
	if (err.type == ERR_NO)
		err = ast_redir_list_dup(&dst_command->redirs, &src_command->redirs);
	if (err.type)
		return (ast_command_free(dst_command), err);
	return (error(ERR_NO));
}

static inline void	ast_command_free_data(t_ast_command *command)
{
	assert(command != NULL);
	if (command->type == AST_CMD_SIMPLE)
		ast_simple_command_free(&command->data.simple);
	else if (command->type == AST_CMD_LIST)
		ast_list_free(&command->data.list);
	else if (command->type == AST_CMD_IF)
		ast_if_free(&command->data.if_clause);
	else if (command->type == AST_CMD_FOR)
		ast_for_free(&command->data.for_clause);
	else if (command->type == AST_CMD_LOOP)
		ast_loop_free(&command->data.loop);
	else if (command->type == AST_CMD_CASE)
		ast_case_free(&command->data.case_clause);
	else if (command->type == AST_CMD_FUNCTION_DEF)
		ast_function_def_free(&command->data.function_def);
}

void	ast_command_free(void *command)
{
	t_ast_command	*cmd;

	assert(command != NULL);
	cmd = (t_ast_command *)command;
	ast_redir_list_free(&cmd->redirs);
	if (cmd->type < AST_CMD_TYPE_COUNT)
		ast_command_free_data(cmd);
	cmd->type = AST_CMD_TYPE_COUNT;
}
