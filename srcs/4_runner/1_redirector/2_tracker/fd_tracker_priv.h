#ifndef FD_TRACKER_PRIV_H
# define FD_TRACKER_PRIV_H

# include "fd_tracker_type.h"
# include "error.h"

# define TRACKER_INITIAL_CAP	128

/* ************************************************************************* */
/*                                  HELPERS                                  */
/* ************************************************************************* */

// @ret ERR_REDIRECTION / ERR_INTERRUPTED / ERR_LIBC
t_error	fd_tracker_backup_priv(
			t_fd_tracker *tracker,
			int fd,
			int *out_backup_fd);
bool	fd_tracker_fd_is_used_by_user(t_fd_tracker *tracker, int fd);
bool	fd_tracker_fd_is_used(t_fd_tracker *tracker, int fd);

#endif
