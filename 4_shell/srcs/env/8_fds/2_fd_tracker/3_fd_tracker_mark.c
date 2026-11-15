/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_fd_tracker_mark.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:12:31 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:12:32 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fd_tracker.h"

t_error	fd_tracker_mark_temp(t_fd_tracker *tracker, int fd)
{
	t_error	err;

	if (fd < TRACKER_MIN_FD_SHELL)
		return (error(ERR_NO));
	err = fd_tracker_protect(tracker, fd);
	if (err.type)
		return (err);
	err = fd_tracker_grow(tracker, (size_t)fd + 1);
	if (err.type)
		return (err);
	tracker->data[fd].user_count++;
	return (err);
}

void	fd_tracker_mark_perm(t_fd_tracker *tracker, int fd)
{
	if (fd >= TRACKER_MIN_FD_SHELL && tracker->data[fd].user_count == 0)
		tracker->data[fd].user_count++;
}
