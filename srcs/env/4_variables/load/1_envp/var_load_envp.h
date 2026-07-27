#ifndef VAR_LOAD_ENVP_H
# define VAR_LOAD_ENVP_H

# include "error.h"

/**
 * @brief Load variables from the environment vector.
 *
 * @param envp Environment vector (borrowed, read-only).
 * @return @c ERR_ASSIGNMENT_MISSING_NAME or @c ERR_LIBC.
 */
t_error	var_load_envp(char **envp);

#endif
