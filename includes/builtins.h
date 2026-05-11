#ifndef BUILTINS_H
# define BUILTINS_H

# include "shell.h"

/* ************************************************************************* */
/*                              SPECIAL BUILTINS                             */
/* ************************************************************************* */

// @ret ERR_LIBC
t_error	export_build_envp(const t_shell *shell, char ***dst_envp);
int		export(int argc, char **argv, char **envp, t_shell *shell);

int		readonly(int argc, char **argv, char **envp, t_shell *shell);

int		unset(int argc, char **argv, char **envp, t_shell *shell);

#endif
