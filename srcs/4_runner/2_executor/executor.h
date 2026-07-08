#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "error.h"
# include "ast_type.h"
# include "runner.h"

t_error cmd_execute(
			t_runner *runner,
			t_ast_simple_command *simple_command,
			int *exit_status);

#endif
