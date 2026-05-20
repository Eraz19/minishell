#ifndef BUILTINS_PRIV_H
# define BUILTINS_PRIV_H

/* ************************************************************************* */
/*                              SPECIAL BUILTINS                             */
/* ************************************************************************* */

int		export(int argc, char **argv, char **envp);
int		readonly(int argc, char **argv, char **envp);
int		unset(int argc, char **argv, char **envp);

#endif
