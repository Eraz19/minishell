#ifndef RUNNER_H
# define RUNNER_H

# include "error.h"
// # include "redirect.h"

typedef struct s_runner
{
	// t_redir_stack	redir_stack;
}	t_runner;

void	runner_init(t_runner *runner);
t_error	runner_run(t_runner *runner);
void	runner_free(t_runner *runner);

#endif
