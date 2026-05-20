#ifndef POSIX_HELPERS_H
# define POSIX_HELPERS_H

# include "error.h"
# include <stddef.h>

# define PWD_UNSPECIFIED_VALUE	"undefined (access error)"

// @warning in case of EACCES:
// 			returns ERR_NO and sets *dst to PWD_UNSPECIFIED_VALUE
// @ret ERR_LIBC
t_error	posix_getcwd(char **dst);

// @ret ERR_LIBC
t_error	posix_write(int fd, const char *buff, size_t len);

#endif
