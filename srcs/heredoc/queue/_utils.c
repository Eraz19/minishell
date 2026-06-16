/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 16:13:00 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/16 16:52:07 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "heredoc_queue_.h"

t_error	heredoc_queue_push(t_heredoc_queue *queue, t_heredoc_queue_item item)
{
	if (!vector_push(queue, &item))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	heredoc_queue_pop(t_heredoc_queue *queue, t_heredoc_queue_item *item)
{
	if (queue->len == 0)
		return (ERR_EMPTY_STACK);
	if (!vector_remove(queue, 0, item))
		return (ERR_LIBC);
	return (ERR_NO);
}
