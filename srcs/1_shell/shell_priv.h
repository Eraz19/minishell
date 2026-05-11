#ifndef SHELL_PRIV_H
# define SHELL_PRIV_H

# include "shell.h"

void	shell_init(t_shell *shell);
void	shell_set(t_shell *addr);
void	shell_free(t_shell **shell);

#endif
