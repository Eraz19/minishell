#ifndef FD_MANAGER_H
# define FD_MANAGER_H

# include "error.h"
# include "redirector_type.h"

// @ret ERR_INCOHERENT_STATE / ERR_POSIX_REDIRECTION / ERR_LIBC
t_error	fd_prepare_perm(t_redirector *redirector, int fd);

void	fd_save_perm(t_redirector *redirector, int fd);

// @ret ERR_INCOHERENT_STATE / ERR_POSIX_REDIRECTION / ERR_LIBC
t_error	fd_save_temp(t_redirector *redirector, int fd);

// @ret ERR_POSIX_REDIRECTION / ERR_LIBC
t_error	fd_check_dup_rhs(t_redirector *redirector, int fd);

// @ret ERR_INTERRUPTED / ERR_LIBC
t_error	fd_restore_fds(t_redirector *redirector, t_redir_backup *backup);

// @ret ERR_INDEX_OUT_OF_BOUND / ERR_INTERRUPTED / ERR_LIBC
t_error	fd_restore_last_backup(t_redirector *redirector);

// @ret ERR_INDEX_OUT_OF_BOUND / ERR_INTERRUPTED / ERR_LIBC
t_error	fd_restore_last_frame(t_redirector *redirector);

// @ret ERR_INDEX_OUT_OF_BOUND / ERR_INTERRUPTED / ERR_LIBC
t_error	fd_restore_frame(t_redirector *redirector, t_redir_frame *frame);

// @ret ERR_INDEX_OUT_OF_BOUND / ERR_INTERRUPTED / ERR_LIBC
t_error	fd_restore_stack(t_redirector *redirector);

#endif
