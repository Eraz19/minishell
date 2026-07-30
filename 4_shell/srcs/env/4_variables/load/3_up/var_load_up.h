#ifndef VAR_LOAD_UP_H
# define VAR_LOAD_UP_H

# include "error.h"

/**
 * @brief Load or init @c PS1 @c PS2 and @c PS4 POSIX variables.
 *
 * @return @c ERR_VAR_INVALID_NAME, @c ERR_VAR_READ_ONLY or @c ERR_LIBC.
 */
t_error	var_load_up(void);

#endif
