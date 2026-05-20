#ifndef VAR_LOAD_MANDATORY_H
# define VAR_LOAD_MANDATORY_H

# include "error.h"

// parent_shell_ppid can be NULL (if it is not a subshell).
// @ret ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY / ERR_LIBC.
t_error	var_load_mandatory(const char *parent_shell_ppid);

#endif
