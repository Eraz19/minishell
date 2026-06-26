#ifndef POSIX_HELPERS_H
# define POSIX_HELPERS_H

# include "error.h"
# include <stddef.h>
# include <sys/stat.h>

# define PWD_UNSPECIFIED_VALUE	"undefined (access error)"

// @warning in case of EACCES:
// 			returns ERR_NO and sets *dst to PWD_UNSPECIFIED_VALUE
// @ret ERR_LIBC
t_error	posix_getcwd(char **dst);

// @ret ERR_INTERRUPTED / ERR_LIBC
t_error	posix_write(int fd, const char *buff, size_t len);

// @ret ERR_OPEN_INVALID_USAGE / ERR_INTERRUPTED / ERR_LIBC
t_error	posix_open(const char *path, int oflag, int *out_fd);

// @ret ERR_OPEN_INVALID_USAGE / ERR_INTERRUPTED / ERR_LIBC
t_error	posix_open_with_mode(
	const char *path,
	int oflag,
	mode_t mode,
	int *out_fd);

#endif
