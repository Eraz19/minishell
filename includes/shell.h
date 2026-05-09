#ifndef SHELL_H
# define SHELL_H

# include "builder.h"
# include "function.h"
# include "scanner.h"
# include "params.h"
# include "runner.h"
# include <stdint.h>

typedef struct s_shell
{
	t_params		params;
	t_fun_list		functions;
	t_lexer			lexer;
	t_builder		builder;
	t_runner		runner;
}	t_shell;

void		shell_set(t_shell *addr);

t_shell		*shell_get(void);

const char	*shell_get_name(void);

// parent can be NULL
t_error		shell_start(int argc, char **argv, char **envp, t_shell *parent);

#endif
