#ifndef RUNNER_H
# define RUNNER_H

# include "error.h"
# include "redirector_type.h"

typedef struct s_runner
{
	t_redirector	redirector;
}	t_runner;

void	runner_init(t_runner *runner);
t_error	runner_run(void);
void	runner_free(t_runner *runner);

#endif
