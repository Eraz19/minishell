#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdbool.h>

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

#endif
