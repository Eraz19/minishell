#ifndef WALKER_PRIV_H
# define WALKER_PRIV_H

# include "error.h"
# include "ast.h"
# include "runner.h"

/* -------------------- helpers -------------------- */

t_error	walk_normalize_output(t_error err, t_error *opt_err, int *exit_status);

/* -------------------- walkers -------------------- */

t_error	walk_pipeline(t_runner *runner, t_ast_pipeline *pipeline, int *exit_status);
t_error	walk_and_or(t_runner *runner, t_ast_and_or *and_or, int *exit_status);
t_error	walk_list(t_runner *runner, t_ast_list *list, int *exit_status);
t_error	walk_if(t_runner *runner, t_ast_if *if_clause, int *exit_status);
t_error	walk_for(t_runner *runner, t_ast_for *for_clause, int *exit_status);
t_error	walk_loop(t_runner *runner, t_ast_loop *loop, int *exit_status);
t_error	walk_case(t_runner *runner, t_ast_case *case_clause, int *exit_status);

#endif
