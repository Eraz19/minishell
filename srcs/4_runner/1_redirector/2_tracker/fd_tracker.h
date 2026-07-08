#ifndef FD_TRACKER_H
# define FD_TRACKER_H

# include "error.h"
# include "fd_tracker_type.h"

# define TRACKER_MIN_FD_SHELL	10

/* ************************************************************************* */
/*                                 LIFE CYCLE                                */
/* ************************************************************************* */

void	fd_tracker_init(t_fd_tracker *tracker, t_redir_stack *stack);
void	fd_tracker_free(t_fd_tracker *tracker);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

// @ret ERR_POSIX_REDIRECTION / ERR_LIBC
t_error	fd_tracker_grow(t_fd_tracker *tracker, size_t min_cap);

// @ret ERR_INCOHERENT_STATE / ERR_POSIX_REDIRECTION / ERR_LIBC
t_error	fd_tracker_protect(t_fd_tracker *tracker, int fd);

// @ret ERR_INCOHERENT_STATE / ERR_POSIX_REDIRECTION / ERR_LIBC
t_error	fd_tracker_mark_temp(t_fd_tracker *tracker, int fd);

void	fd_tracker_mark_perm(t_fd_tracker *tracker, int fd);

// @ret ERR_INDEX_OUT_OF_BOUND / ERR_POSIX_REDIRECTION / ERR_INTERRUPTED
// 		/ ERR_LIBC
t_error	fd_tracker_backup(t_fd_tracker *tracker, int fd, int *out_backup_fd);

void	fd_tracker_unlock(t_fd_tracker *tracker, int fd);

bool	fd_tracker_fd_is_used_by_shell(t_fd_tracker *tracker, int fd);

#endif
