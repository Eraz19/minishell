/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_fd_save.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:12:52 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:12:53 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fd.h"
#include "posix_helpers.h"
#include "fd_tracker.h"
#include "redirect_stack.h"
#include "env.h"

// @ret ERR_INTERNAL
t_error	fd_save_perm(int fd)
{
	t_fd_manager	*fd_manager;
	t_error			err;

	err = env_get_fd_manager(&fd_manager);
	if (err.type)
		return (err);
	fd_tracker_mark_perm(&fd_manager->tracker, fd);
	return (err);
}

// @ret ERR_INTERNAL / ERR_REDIRECTION / ERR_LIBC
t_error	fd_save_temp(int fd)
{
	t_fd_manager	*fd_manager;
	t_redir_backup	backup;
	t_error			err;

	err = env_get_fd_manager(&fd_manager);
	if (err.type)
		return (err);
	backup.fd = fd;
	err = fd_tracker_mark_temp(&fd_manager->tracker, fd);
	if (err.type)
		return (err);
	err = fd_tracker_backup(&fd_manager->tracker, fd, &backup.backup_fd);
	if (err.type)
		return (fd_tracker_unlock(&fd_manager->tracker, fd), err);
	err = redirect_frame_push(&fd_manager->stack, &backup);
	if (err.type)
	{
		fd_tracker_unlock(&fd_manager->tracker, backup.fd);
		fd_tracker_unlock(&fd_manager->tracker, backup.backup_fd);
		if (backup.backup_fd >= 0)
			error_priorize(err, posix_close_if_open(backup.backup_fd));
	}
	return (err);
}
