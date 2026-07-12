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

// @ret ERR_INTERRUPTED / ERR_POSIX_WRITE
t_error	posix_write(int fd, const char *buff, size_t len);

// @ret ERR_INTERRUPTED / ERR_LIBC
t_error	posix_read(int fd, void *buff, size_t len, size_t *bytes_read);

// @ret ERR_INVALID_USAGE / ERR_INTERRUPTED / ERR_LIBC
t_error	posix_open(const char *path, int oflag, int *out_fd);

// @ret ERR_INVALID_USAGE / ERR_INTERRUPTED / ERR_LIBC
t_error	posix_open_with_mode(
	const char *path,
	int oflag,
	mode_t mode,
	int *out_fd);

// @warning on Linux the fd is released even on EINTR, which is reported as
//			success; never call close() on the same fd afterwards.
// @ret ERR_INTERRUPTED / ERR_LIBC
t_error	posix_close(int fd);

// uses posix_close() and ignore EBADF errors
// @ret ERR_INTERRUPTED / ERR_LIBC
t_error	posix_close_if_open(int fd);

// @ret ERR_INTERRUPTED / ERR_LIBC
t_error	posix_dup(int fd, int *out);

// @ret ERR_INTERRUPTED / ERR_LIBC
t_error	posix_dup2(int fd_from, int fd_to);

// @note always retry before returning ERR_INTERRUPTED
// @ret ERR_LIBC / ERR_INTERRUPTED
t_error	posix_wait(pid_t pid, int *exit_status);

// @note always retry before returning ERR_INTERRUPTED
// @ret ERR_LIBC / ERR_INTERRUPTED
t_error	posix_wait_with_options(pid_t pid, int options, int *exit_status);

#endif
