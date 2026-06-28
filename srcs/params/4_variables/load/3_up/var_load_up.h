#ifndef VAR_LOAD_UP_H
# define VAR_LOAD_UP_H

# include "error.h"

/**
 * @brief Load variables from the parent shell state.
 *
 * @return `ERR_VAR_INVALID_NAME`, `ERR_VAR_READ_ONLY` or `ERR_LIBC`.
 */
t_error	var_load_up(void);

#endif
