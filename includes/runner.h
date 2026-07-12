#ifndef RUNNER_H
# define RUNNER_H

# include "error.h"
# include "redirector_type.h"
# include "functions.h"
# include "cmd_cache.h"

typedef struct s_runner
{
	t_redirector	redirector;
	t_functions		functions;
	t_cmd_cache		cmd_cache;
	size_t			loop_depth;
	size_t			control_depth;
}	t_runner;

void	runner_init(t_runner *runner);
t_error	runner_run(t_runner *runner);
void	runner_free(t_runner *runner);

#endif
