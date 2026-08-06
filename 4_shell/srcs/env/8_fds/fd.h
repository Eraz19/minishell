/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:13:00 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 15:10:29 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FD_H
# define FD_H

# include "fd_tracker_type.h"
# include "redirect_stack_type.h"
# include "error.h"

// TODO: doc
typedef struct s_fd_manager
{
	/** @brief Maximum number of stack frames allocated so far. */
	size_t			max_frame_count;
	/** @brief Redirection backup stack managed by redirect_stack submodule. */
	t_redir_stack	stack;
	/** @brief File-descriptor tracker managed by the fd_tracker submodule. */
	t_fd_tracker	tracker;
	size_t			heredoc_id;
}	t_fd_manager;

/* -------------------- LIFE CYCLE -------------------- */

void	fd_init(t_fd_manager *fd_manager);

void	fd_init_subshell(t_fd_manager *fd_manager);

// @ret ERR_NO if restore_redirections == false
// @ret ERR_NO / ERR_INTERNAL / ERR_LIBC if restore_redirections == true
t_error	fd_clear(t_fd_manager *fd_manager, bool restore_redirections);

void	fd_free(t_fd_manager *fd_manager);

/* -------------------- OPS -------------------- */

// @ret ERR_NO / ERR_INTERNAL / ERR_REDIRECTION / ERR_LIBC
t_error	fd_prepare_perm(int fd);

// @ret ERR_NO / ERR_INTERNAL
t_error	fd_save_perm(int fd);

// @ret ERR_NO / ERR_INTERNAL / ERR_REDIRECTION / ERR_LIBC
t_error	fd_save_temp(int fd);

// @ret ERR_NO / ERR_REDIRECTION / ERR_LIBC
t_error	fd_check_dup_rhs(int fd);

// @ret ERR_NO / ERR_REDIRECTION / ERR_INTERNAL / ERR_LIBC
t_error	fd_open_heredoc(t_string *path, int *fd);

// @ret ERR_NO / ERR_INTERNAL / ERR_LIBC
t_error	fd_restore_last_backup(void);

// @ret ERR_NO / ERR_INTERNAL / ERR_LIBC
t_error	fd_restore_last_frame(void);

// @ret ERR_NO / ERR_INTERNAL / ERR_LIBC
t_error	fd_restore_stack(void);

// @ret ERR_NO / ERR_INTERNAL / ERR_LIBC
t_error	fd_use_new_frame(void);

#endif
