/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_tracker_priv.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:12:40 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:12:41 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

/**
 * @brief Print the standard "all file descriptors are already used" error.
 *
 * @return Error descriptor carrying @c ERR_REDIRECTION.
 */
t_error	redirect_print_error_all_fd_used(void);

#endif
