/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_fd_tracker_is_used.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:12:33 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:12:34 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fd_tracker_priv.h"
#include "fd_tracker.h"

bool	fd_tracker_fd_is_used_by_user(t_fd_tracker *tracker, int fd)
{
	return (fd < TRACKER_MIN_FD_SHELL
		|| ((size_t)fd < tracker->cap && tracker->data[fd].user_count > 0));
}

bool	fd_tracker_fd_is_used_by_shell(t_fd_tracker *tracker, int fd)
{
	return (fd >= TRACKER_MIN_FD_SHELL
		&& (size_t)fd < tracker->cap
		&& tracker->data[fd].is_used_by_shell);
}

bool	fd_tracker_fd_is_used(t_fd_tracker *tracker, int fd)
{
	return (fd_tracker_fd_is_used_by_user(tracker, fd)
		|| fd_tracker_fd_is_used_by_shell(tracker, fd));
}
