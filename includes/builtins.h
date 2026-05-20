#ifndef BUILTINS_H
# define BUILTINS_H

# include "shell.h"

typedef int (*t_builtin_function)(int argc, char **argv, char **envp);

typedef struct s_builtin
{
	const char			*name;
	t_builtin_function	function;
}	t_builtin;

/* ************************************************************************* */
/*                                   GETTER                                  */
/* ************************************************************************* */

/*
SPECIALS:
	- Searched first during Command Search.
	- Shell exits on error (if invoked directly && shell is non-interactive).
REGULAR / INTRINSICS:
	- Searched right after functions during Command Search.
	- Shell does not exit on error.
*/
t_builtin_function	builtins_get(const char *name, bool special);

// TODO: move to params module!
// @ret ERR_LIBC
t_error	export_build_envp(const t_shell *shell, char ***dst_envp);

#endif
