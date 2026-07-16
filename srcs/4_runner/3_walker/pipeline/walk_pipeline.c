#include "walker_priv.h"
#include "walk_pipeline_priv.h"
#include "params.h"
# include <assert.h>	// DEBUG
# include <stdio.h>		// DEBUG
# include "logs.h"		// DEBUG

t_error	walk_pipeline(
			t_runner *runner,
			t_ast_pipeline *pipeline,
			int *exit_status)
{
	t_error	err;

	assert(pipeline->commands.len > 0);
	*exit_status = -1;
	if (pipeline->commands.len == 1)
		err = walk_pipe_single_command(runner, pipeline, exit_status);
	else
		err = walk_pipe_multiple_commands(runner, pipeline, exit_status);
	if (*exit_status < 0)
		*exit_status = (int)err.type;
	// err = walk_normalize_output(err, NULL, exit_status);
	fprintf(stderr, "%s[WALKER] $? = %i%s\n", YELLOW, *exit_status, NC);
	params_set_last_status(*exit_status);
	return (err);
}
