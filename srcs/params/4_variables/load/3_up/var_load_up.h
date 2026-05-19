#ifndef VAR_LOAD_UP_H
# define VAR_LOAD_UP_H

#include "variables.h"

// @ret ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY / ERR_LIBC.
t_error	var_load_up(t_var_list *variables);

#endif
