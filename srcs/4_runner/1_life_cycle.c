#include "runner.h"
#include "redirector.h"

void	runner_init(t_runner *runner)
{
	redirect_init(&runner->redirector);
	functions_init(&runner->functions);
}

void	runner_free(t_runner *runner)
{
	redirect_free(&runner->redirector);
	functions_free(&runner->functions);
}
