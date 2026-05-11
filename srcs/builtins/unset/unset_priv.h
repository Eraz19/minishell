#ifndef UNSET_PRIV_H
# define UNSET_PRIV_H

#include "error.h"
#include "shell.h"

// Errors: ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY / ERR_INDEX_OUT_OF_BOUND
t_error	unset_var(const char *builtin, int argc, char **argv, t_shell *shell);

// TODO
t_error	unset_fun(const char *builtin, int argc, char **argv, t_shell *shell);

#endif
