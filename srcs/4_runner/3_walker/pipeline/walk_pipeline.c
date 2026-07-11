#include "walker_priv.h"
#include "walk_pipeline_priv.h"
#include "params.h"

t_error	walk_pipeline(
			t_runner *runner,
			t_ast_pipeline *pipeline,
			int *exit_status)
{
	t_error	err;

	*exit_status = -1;
	if (pipeline->commands.len == 1)
		err = walk_pipe_single_command(runner, pipeline, exit_status);
	else
		err = walk_pipe_multiple_commands(runner, pipeline, exit_status);
	err = walk_normalize_output(err, NULL, exit_status);
	params_set_last_status(*exit_status);
	return (err);
}
