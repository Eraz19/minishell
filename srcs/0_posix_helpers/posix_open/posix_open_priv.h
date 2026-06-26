#ifndef POSIX_OPEN_PRIV_H
# define POSIX_OPEN_PRIV_H

# include "error.h"
# include <sys/stat.h>

t_error	open_check_ub_args(int oflag, mode_t *optional_mode);

#endif
