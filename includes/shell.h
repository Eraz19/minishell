#ifndef SHELL_H
# define SHELL_H

# include <stdint.h>
# include "alias.h"
# include "params.h"
# include "runner.h"
# include "history.h"
# include "scanner.h"
# include "heredoc.h"
# include "builder.h"

typedef struct s_shell
{
	t_alias		alias;
	t_builder	builder;
	t_heredoc	heredoc;
	t_history	history;
	t_params	params;
	t_runner	runner;
	t_scanner	scanner;
}	t_shell;

t_error		shell_run(int argc, char **argv, char **envp);
t_shell		*shell_get(void);
const char	*shell_get_name(void);
void		shell_free(void);
void		shell_exit_on_veof(void);	// TODO: remove

// Les fonctions pour les enfaaaaaants

t_alias		*shell_get_alias(void);
t_builder	*shell_get_builder(void);
t_heredoc	*shell_get_heredoc(void);
t_history	*shell_get_history(void);
t_params	*shell_get_params(void);
t_runner	*shell_get_runner(void);
t_scanner	*shell_get_scanner(void);

#endif
