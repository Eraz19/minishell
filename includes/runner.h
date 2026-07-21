#ifndef RUNNER_H
# define RUNNER_H

# include "runner_type.h"
# include "shell.h"

// TODO: doc

// Life cycle

void	runner_init(t_runner *runner, t_cmd_cache *cmd_cache);
void	runner_clear(t_runner *runner);
void	runner_free(t_runner *runner);

// Ops

void	runner_run(t_shell *shell);

#endif
