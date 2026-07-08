#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "error.h"
# include "runner.h"
# include "ast_type.h"

t_error cmd_execute(t_runner *runner, t_ast_simple_command *simple_command);

#endif
