#ifndef SHELL_H
# define SHELL_H

# include "params.h"
# include "history.h"
# include "scanner.h"
# include "builder.h"
# include "runner.h"
# include <stdint.h>

typedef struct s_shell
{
	t_params	params;
	t_history	history;
	t_scanner	scanner;
	t_builder	builder;
	t_runner	runner;
}	t_shell;

t_error		shell_start(int argc, char **argv, char **envp);
t_shell		*shell_get(void);
const char	*shell_get_name(void);
void		shell_exit(t_error error);
void		shell_exit_on_veof(void);

// Les fonctions pour les enfaaaaaants

t_params	*shell_get_params(void);
t_history	*shell_get_history(void);
t_scanner	*shell_get_scanner(void);
t_builder	*shell_get_builder(void);
t_runner	*shell_get_runner(void);

#endif
