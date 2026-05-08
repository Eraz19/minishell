#ifndef BUILTINS_H
# define BUILTINS_H

# include "variable.h"

/* ---------- TMP ---------- */

typedef struct s_shell
{
	t_var_list	variables;
	void		*functions;	// TODO
}	t_shell;

/* ------------------------- */

/* ************************************************************************* */
/*                              SPECIAL BUILTINS                             */
/* ************************************************************************* */

int		export(int argc, char **argv, char **envp, t_shell *shell);
t_error	export_build_envp(const t_shell *shell, char ***dst_envp);
int		readonly(int argc, char **argv, char **envp, t_shell *shell);
int		unset(int argc, char **argv, char **envp, t_shell *shell);

#endif
