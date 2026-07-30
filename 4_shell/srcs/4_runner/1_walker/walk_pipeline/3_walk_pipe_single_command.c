#include "walker.h"
#include "walk_pipeline_priv.h"

t_error	walk_pipe_single_command(
			t_runner *runner,
			t_ast_pipeline *pipeline,
			int *exit_status)
{
	t_ast_command	*command;
	t_error			err;

	command = &((t_ast_command *)pipeline->commands.data)[0];
	err = walk_command(runner, command, exit_status);
	if (pipeline->negated == true)
		*exit_status = (int)(*exit_status == 0);
	return (err);
}
