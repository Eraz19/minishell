#include "runner.h"
#include "redirector.h"

void	runner_init(t_runner *runner)
{
	redirect_init(&runner->redirector);
	functions_init(&runner->functions);
	cmd_cache_init(&runner->cmd_cache);
	runner->loop_depth = 0;
	runner->control_depth = 0;
}

void	runner_free(t_runner *runner)
{
	redirect_free(&runner->redirector);
	functions_free(&runner->functions);
	cmd_cache_free(&runner->cmd_cache);
	runner->loop_depth = 0;
	runner->control_depth = 0;
}
