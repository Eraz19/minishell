#ifndef RUNNER_H
# define RUNNER_H

# include "error.h"
# include "runner_type.h"
# include "shell.h"

// TODO: doc

// Life cycle

void	runner_init(t_runner *runner);
void	runner_init_subshell(t_runner *runner);
t_error	runner_clear(t_runner *runner);
void	runner_free(t_runner *runner);

// Ops

t_error	runner_run(t_shell *shell);

#endif
