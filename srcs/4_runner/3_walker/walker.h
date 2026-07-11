#ifndef WALKER_H
# define WALKER_H

# include "error.h"
# include "ast.h"
# include "runner.h"

t_error	walk(t_runner *runner, t_ast_root *ast_root, int *exit_status);
t_error	walk_command(t_runner *runner, t_ast_command *command, int *exit_status);

#endif
