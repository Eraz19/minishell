#ifndef VAR_LOAD_ENVP_H
# define VAR_LOAD_ENVP_H

#include "variables.h"

// @ret ERR_VAR_NOT_FOUND / ERR_VAR_READ_ONLY / ERR_LIBC.
t_error	var_load_envp(t_var_list *variables, char **envp);

#endif
