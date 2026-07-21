#include "runner.h"

void	runner_init(t_runner *runner, t_cmd_cache *cmd_cache)
{
	runner->cmd_cache = cmd_cache;
	runner->loop_depth = 0;
	runner->control_depth = 0;
}

void	runner_clear(t_runner *runner)
{
	runner->loop_depth = 0;
	runner->control_depth = 0;
}

void	runner_free(t_runner *runner)
{
	runner->loop_depth = 0;
	runner->control_depth = 0;
}
