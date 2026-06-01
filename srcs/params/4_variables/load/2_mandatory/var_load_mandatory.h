#ifndef VAR_LOAD_MANDATORY_H
# define VAR_LOAD_MANDATORY_H

# include "error.h"

// @ret ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY / ERR_LIBC.
t_error	var_load_mandatory(void);

#endif
