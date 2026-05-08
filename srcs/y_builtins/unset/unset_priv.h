#ifndef UNSET_PRIV_H
# define UNSET_PRIV_H

#include "builtins.h"

t_error	unset_var_all(const char *builtin, int argc, char **argv, t_shell *shell);
t_error	unset_fun_all(const char *builtin, int argc, char **argv, t_shell *shell);

#endif
