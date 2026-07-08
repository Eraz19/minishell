#ifndef WALKER_H
# define WALKER_H

# include "error.h"
# include "ast_type.h"
# include "runner.h"

/* --- PUBLIC --- */

t_error	walk(t_runner *runner, t_ast_root *ast_root);

/* --- LIST WALKER (INTERNAL) --- */
t_error	walk_command(t_runner *runner, t_ast_command *command);
t_error	walk_pipeline(t_runner *runner, t_ast_pipeline *pipeline);
t_error	walk_and_or(t_runner *runner, t_ast_and_or *and_or);

/* --- LIST WALKER (PRIVATE) --- */
t_error	walk_list(t_runner *runner, t_ast_list *list);

/* --- CONTROL WALKER (PRIVATE) --- */
t_error	walk_if(t_runner *runner, t_ast_if *if_clause);
t_error	walk_for(t_runner *runner, t_ast_for *for_clause);
t_error	walk_loop(t_runner *runner, t_ast_loop *loop);
t_error	walk_case(t_runner *runner, t_ast_case *case_clause);
t_error	walk_func(t_runner *runner, t_ast_function_def *function_def, t_ast_redir_list *redirs);

#endif
