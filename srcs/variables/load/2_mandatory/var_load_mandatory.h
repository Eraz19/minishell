#ifndef VAR_LOAD_MANDATORY_H
# define VAR_LOAD_MANDATORY_H

# include "variable.h"

// parent_shell_ppid can be NULL (if it is not a subshell)
// Errors can be ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY / ERR_LIBC.
t_error	var_load_mandatory(t_var_list *variables, char *parent_shell_ppid);

#endif
