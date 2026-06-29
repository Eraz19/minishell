#ifndef POSIX_HELPERS_H
# define POSIX_HELPERS_H

# include "error.h"
# include "libft.h"
# include <stdbool.h>
# include <stddef.h>
# include <sys/stat.h>

# define PWD_UNSPECIFIED_VALUE	"undefined (access error)"

// @ret ERR_SIZE_MAX_REACHED / ERR_LIBC
t_error	posix_getcwd(t_string *dst);

// @ret ERR_INTERRUPTED / ERR_LIBC
t_error	posix_write(int fd, const char *buff, size_t len);

// @ret ERR_INTERRUPTED / ERR_LIBC
t_error	posix_read(int fd, void *buff, size_t len, size_t *bytes_read);

// @ret ERR_OPEN_INVALID_USAGE / ERR_INTERRUPTED / ERR_LIBC
t_error	posix_open(const char *path, int oflag, int *out_fd);

// @ret ERR_OPEN_INVALID_USAGE / ERR_INTERRUPTED / ERR_LIBC
t_error	posix_open_with_mode(
	const char *path,
	int oflag,
	mode_t mode,
	int *out_fd);

// @warning on Linux the fd is released even on EINTR, which is reported as
//			success; never call close() on the same fd afterwards.
// @ret ERR_LIBC
t_error	posix_close(int fd);

#endif
