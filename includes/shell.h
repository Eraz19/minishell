#ifndef SHELL_H
# define SHELL_H

# include "builder.h"
# include "scanner.h"
# include "params.h"
# include "runner.h"
# include <stdint.h>

typedef struct s_shell
{
	t_params		params;
	t_lexer			lexer;
	t_builder		builder;
	t_runner		runner;
}	t_shell;

// parent MUST be NULL if not a subshell
t_error		shell_start(int argc, char **argv, char **envp, t_shell *parent);
t_shell		*shell_get(void);
const char	*shell_get_name(void);
void		shell_exit(t_error error);
void		shell_exit_on_veof(void);
// is public for params module to use it
void		shell_free(t_shell **shell);

#endif
