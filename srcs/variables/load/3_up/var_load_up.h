#ifndef VAR_LOAD_UP_H
# define VAR_LOAD_UP_H

#include "variable.h"

// Errors can be ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY / ERR_LIBC.
t_error	var_init_up(t_var_list *variables);

#endif
