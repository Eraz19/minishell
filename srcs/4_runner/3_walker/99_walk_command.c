#include "error.h"
#include "walker.h"
#include "walker_priv.h"
#include "executor.h"
#include "params.h"
# include "debug.h"

static inline t_error	walk_command_dispatch(
							t_runner *runner,
							t_ast_command *command,
							int *exit_status)
{
	t_error	err;

	// TODO: AST_CMD_CASE
	if (command->type == AST_CMD_SIMPLE)
		return (cmd_execute(runner, &command->data.simple, exit_status));
	else if (command->type == AST_CMD_LIST)
		return (walk_list(runner, &command->data.list, exit_status));
	else if (command->type == AST_CMD_IF)
		return (walk_if(runner, &command->data.if_clause, exit_status));
	else if (command->type == AST_CMD_FOR)
		return (walk_for(runner, &command->data.for_clause, exit_status));
	else if (command->type == AST_CMD_LOOP)
		return (walk_loop(runner, &command->data.loop, exit_status));
	else if (command->type == AST_CMD_FUNCTION_DEF)
	{
		err = params_set_function(&command->data.function_def);
		*exit_status = (int)err.type;
		return (err);
	}
	return (error_print(error(ERR_NOT_IMPLEMENTED), "walker", NULL,
			"command type %s", ast_command_type_to_string(command->type)));
}

t_error	walk_command(t_runner *runner, t_ast_command *command, int *exit_status)
{
	t_error	err;

	*exit_status = -1;
	// TODO: handle redirs
	err = walk_command_dispatch(runner, command, exit_status);
	return (walk_normalize_output(err, NULL, exit_status));
}
