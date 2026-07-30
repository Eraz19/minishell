#ifndef WALKER_H
# define WALKER_H

# include "cmd.h"

t_error	walk(t_runner *runner, t_ast_root *ast_root);
t_error	walk_command(t_runner *runner, t_ast_command *command, int *exit_status);
t_error	walk_function(t_cmd *cmd, t_runner *runner, int *status);

#endif
