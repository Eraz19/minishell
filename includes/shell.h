#ifndef SHELL_H
# define SHELL_H

# include "builder.h"
# include "function.h"
# include "scanner.h"
# include "params.h"
# include "runner.h"
# include "variable.h"
# include <stdint.h>

typedef struct s_shell
{
	t_shell_params	params;
	t_var_list		variables;
	t_fun_list		functions;
	t_lexer			lexer;
	t_builder		builder;
	t_runner		runner;
}	t_shell;

// parent_shell can be NULL
t_error	shell_start(int argc, char **argv, char **envp, t_shell *parent_shell);

#endif
