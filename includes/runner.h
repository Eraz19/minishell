#ifndef RUNNER_H
# define RUNNER_H

# include "runner_type.h"
# include "ast.h"

// Life cycle

t_error	runner_init(
			t_runner *runner,
			t_runner *parent_runner,
			t_scanner *parent_scanner,
			t_scan_mode mode);
void	runner_clear(t_runner *runner);
void	runner_free(t_runner *runner);
void	runner_free_void(void *runner);

// Ops

// TODO: doc
void	runner_run(t_runner *runner);
void	runner_run_ast(t_runner *runner, t_ast_root *ast_root);

#endif
