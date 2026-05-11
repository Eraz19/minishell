#ifndef POSIX_HELPERS_H
# define POSIX_HELPERS_H

# include "error.h"
# include <stddef.h>

// @ret ERR_LIBC
t_error	posix_write(int fd, const char *buff, size_t len);

#endif
