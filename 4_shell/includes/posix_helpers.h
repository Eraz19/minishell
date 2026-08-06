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

// @ret ERR_NO / ERR_POSIX_WRITE
t_error	posix_write(int fd, const char *buff, size_t len);

// @ret ERR_NO / ERR_LIBC
t_error	posix_read_all(int fd, t_string *out);

// @ret ERR_NO / ERR_LIBC
t_error	posix_read_until_c(int fd, t_string *out, char c);

// @ret ERR_INVALID_USAGE / ERR_LIBC
t_error	posix_open(const char *path, int oflag, int *out_fd);

// @ret ERR_INVALID_USAGE / ERR_LIBC
t_error	posix_open_with_mode(
	const char *path,
	int oflag,
	mode_t mode,
	int *out_fd);

// @ret ERR_NO / ERR_LIBC
t_error	posix_close_if_open(int fd);

// @ret ERR_NO / ERR_LIBC
t_error	posix_dup(int fd, int *out);

// @ret ERR_NO / ERR_LIBC
t_error	posix_dup2(int fd_from, int fd_to);

// @ret ERR_NO / ERR_LIBC
t_error	posix_wait(pid_t pid, int *exit_status);

// @ret ERR_NO / ERR_LIBC
t_error	posix_wait_and_retry(pid_t pid, int *exit_status);

// @ret ERR_NO / ERR_LIBC
t_error	posix_wait_with_opt(pid_t pid, int options, int *exit_status);

// @ret ERR_NO / ERR_LIBC
t_error	posix_wait_with_opt_and_retry(pid_t pid, int options, int *exit_status);

#endif
