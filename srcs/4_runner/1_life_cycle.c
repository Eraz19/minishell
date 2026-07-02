#include "runner.h"
#include "redirector.h"

void	runner_init(t_runner *runner)
{
	redirect_init(&runner->redirector);
}

void	runner_free(t_runner *runner)
{
	redirect_free(&runner->redirector);
}
