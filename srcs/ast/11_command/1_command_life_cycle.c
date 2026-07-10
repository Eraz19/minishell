#include "converter_priv.h"
#include <stdlib.h>
# include <assert.h>	// DEBUG

void	ast_command_init(t_ast_command *command)
{
	assert(command != NULL);
	command->type = AST_CMD_TYPE_COUNT;
	ast_redir_list_init(&command->redirs);
	command->data = (t_ast_command_data){ 0 };
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
