#ifndef VAR_LOAD_MANDATORY_PRIV_H
# define VAR_LOAD_MANDATORY_PRIV_H

# include "error.h"

// @ret ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY / ERR_LIBC.
t_error	var_set_ifs(void);

// @ret ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY / ERR_LIBC.
t_error	var_set_pwd(void);

// parent_shell_ppid can be NULL (if it is not a subshell).
// @ret ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY / ERR_LIBC.
t_error	var_set_ppid(const char *parent_shell_ppid);

#endif
