#include "error.h"
#include "walker.h"
#include "walker_priv.h"
#include "executor.h"
#include "params.h"
# include "debug.h"

t_error	walk_command(t_runner *runner, t_ast_command *command, int *exit_status)
{
	t_error	err;

	// TODO: AST_CMD_CASE
	// TODO: handle redirs
	*exit_status = -1;
	if (command->type == AST_CMD_SIMPLE)
		err = cmd_execute(runner, &command->data.simple, exit_status);
	else if (command->type == AST_CMD_LIST)
		err = walk_list(runner, &command->data.list, exit_status);
	else if (command->type == AST_CMD_IF)
		err = walk_if(runner, &command->data.if_clause, exit_status);
	else if (command->type == AST_CMD_FOR)
		err = walk_for(runner, &command->data.for_clause, exit_status);
	else if (command->type == AST_CMD_LOOP)
		err = walk_loop(runner, &command->data.loop, exit_status);
	else if (command->type == AST_CMD_FUNCTION_DEF)
	{
		err = params_set_function(&command->data.function_def);
		if (err.type == ERR_NO)
			*exit_status = 0;
	}
	else
		err = (error_print(error(ERR_NOT_IMPLEMENTED), "walker", NULL,
			"command type %s", ast_command_type_to_string(command->type)));
	return (walk_normalize_output(err, NULL, exit_status));
}
