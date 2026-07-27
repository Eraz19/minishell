#ifndef VAR_LOAD_MANDATORY_H
# define VAR_LOAD_MANDATORY_H

# include "error.h"

/**
 * @brief Load the mandatory variables required by the shell.
 *
 * @return @c ERR_VAR_INVALID_NAME, @c ERR_VAR_READ_ONLY or @c ERR_LIBC.
 */
t_error	var_load_mandatory(void);

#endif
