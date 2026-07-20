#include "runner.h"
#include "redirector.h"

void	runner_init(t_runner *runner, t_cmd_cache *cmd_cache)
{
	redirect_init(&runner->redirector);
	runner->cmd_cache = cmd_cache;
	runner->loop_depth = 0;
	runner->control_depth = 0;
}

void	runner_init_subshell(t_runner *runner)
{
	redirect_init_subshell(&runner->redirector);
}

t_error	runner_clear(t_runner *runner)
{
	runner->loop_depth = 0;
	runner->control_depth = 0;
	return (redirect_clear(&runner->redirector, true));
}

void	runner_free(t_runner *runner)
{
	redirect_free(&runner->redirector);
	runner->loop_depth = 0;
	runner->control_depth = 0;
}
