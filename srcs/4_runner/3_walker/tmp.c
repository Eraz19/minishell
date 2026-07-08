#include "error.h"
#include "walker.h"
#include "executor.h"

t_error	walk_command(t_runner *runner, t_ast_command *command)
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
	if (command->type == AST_CMD_SIMPLE)
		return (cmd_execute(runner, &command->data.simple));
	return (error_print(error(ERR_NOT_IMPLEMENTED), "walker", NULL, "command type %i", command->type));
}

t_error	walk_pipeline(t_runner *runner, t_ast_pipeline *pipeline)
{
	size_t			i;
	t_ast_command	*command;
	t_error			err;

	i = 0;
	while (i < pipeline->commands.len)
	{
		// TODO: negated
		command = &((t_ast_command *)pipeline->commands.data)[i];
		err = walk_command(runner, command);
		if (err.type)
			return (err);
		i++;
	}
	return (error(ERR_NO));
}

t_error	walk_and_or(t_runner *runner, t_ast_and_or *and_or)
{
	size_t			i;
	t_ast_pipeline	*pipeline;
	t_error			err;

	i = 0;
	while (i < and_or->pipelines.len)
	{
		// TODO: next_on_success
		pipeline = &((t_ast_pipeline *)and_or->pipelines.data)[i];
		err = walk_pipeline(runner, pipeline);
		if (err.type)
			return (err);
		i++;
	}
	return (error(ERR_NO));
}

t_error	walk(t_runner *runner, t_ast_root *ast_root)
{
	size_t			i;
	t_ast_and_or	*and_or;
	t_error			err;

	i = 0;
	while (i < ast_root->and_ors.len)
	{
		// TODO: subshell
		// TODO: async
		and_or = &((t_ast_and_or *)ast_root->and_ors.data)[i];
		err = walk_and_or(runner, and_or);
		if (err.type)
			return (err);
		i++;
	}
	return (error(ERR_NO));
}
