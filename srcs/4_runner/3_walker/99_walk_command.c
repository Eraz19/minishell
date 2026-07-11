#include "error.h"
#include "walker.h"
#include "executor.h"
#include "params.h"
# include "debug.h"

t_error	walk_command(t_runner *runner, t_ast_command *command, int *exit_status)
{
	/*
	TODO: handle types:
		AST_CMD_SIMPLE,
		AST_CMD_LIST,
		AST_CMD_IF,
		AST_CMD_FOR,
		AST_CMD_LOOP,
		AST_CMD_CASE,
		AST_CMD_FUNCTION_DEF,
		AST_CMD_TYPE_COUNT
	TODO: handle redirs
	*/
	// TODO: exit status
	if (command->type == AST_CMD_SIMPLE)
		return (cmd_execute(runner, &command->data.simple, exit_status));
	else if (command->type == AST_CMD_FUNCTION_DEF)
		return (params_set_function(&command->data.function_def));
	return (error_print(error(ERR_NOT_IMPLEMENTED), "walker", NULL,
		"command type %s", ast_command_type_to_string(command->type)));
}
