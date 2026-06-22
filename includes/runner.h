#ifndef RUNNER_H
# define RUNNER_H

# include "error.h"

typedef struct s_runner
{
	// TODO;
}	t_runner;

void	runner_init(t_runner *runner);
t_error	runner_run(t_runner *runner);
void	runner_free(t_runner *runner);

#endif
