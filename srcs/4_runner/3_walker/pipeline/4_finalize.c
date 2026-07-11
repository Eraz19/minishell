#include "walker_priv.h"
#include "walk_pipeline_priv.h"

static inline t_error	walk_pipe_wait_all(t_pipe_run *run)
{
	size_t	i;
	pid_t	pid;
	int		child_status;
	t_error	last_err;
	t_error	err;

	i = 0;
	last_err = error(ERR_NO);
	err = last_err;
	while (i < run->command_id)
	{
		pid = run->pids[i++];
		if (pid == 0)
			continue ;
		child_status = -1;
		last_err = walk_wait(pid, &child_status);
		if (child_status >= 0)
		{
			run->exit_status = child_status;
			if (child_status > 0)
				run->last_failure = child_status;
		}
		err = error_priorize(err, last_err);
	}
	return (err);
}

/*
pipefail off, ! off: status = status de la dernière command
pipefail off, ! on: status = 0 si dernière command != 0, sinon 1
pipefail on, ! off: status = 0 si toutes les commands ont status 0, sinon status de la dernière/rightmost command non-zero
pipefail on, ! on: status = 0 si au moins une command a status non-zero, sinon 1
*/
t_error	walk_pipe_finalize(t_pipe_run *run)
{
	t_error	err;

	err = walk_pipe_wait_all(run);
	if (run->exit_status >= 0)
	{
		if (run->pipefail_is_active == true)
		{
			if (run->pipeline->negated == false)
				run->exit_status = run->last_failure;
			else
				run->exit_status = (int)(run->last_failure == 0);
		}
		else if (run->pipeline->negated == true)
				run->exit_status = (int)(run->exit_status == 0);
	}
	return (err);
}
