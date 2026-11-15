/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_fd_tracker_life_cycle.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:12:26 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:12:27 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fd_tracker.h"
#include <stdlib.h>

void	fd_tracker_init(t_fd_tracker *tracker, t_redir_stack *stack)
{
	tracker->stack = stack;
	tracker->data = NULL;
	tracker->cap = 0;
	tracker->next_available = TRACKER_MIN_FD_SHELL;
}

void	fd_tracker_free(t_fd_tracker *tracker)
{
	if (tracker->data)
		free(tracker->data);
	fd_tracker_init(tracker, tracker->stack);
}
