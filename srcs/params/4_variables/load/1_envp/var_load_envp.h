#ifndef VAR_LOAD_ENVP_H
# define VAR_LOAD_ENVP_H

#include "error.h"

// @ret ERR_SHELL_NOT_FOUND / ERR_VAR_READ_ONLY / ERR_LIBC.
t_error	var_load_envp(char **envp);

#endif
