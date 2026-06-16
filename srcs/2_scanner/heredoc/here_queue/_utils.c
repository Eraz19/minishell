/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 16:13:00 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/16 13:16:41 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "__here_queue.h"

t_error	here_queue_push(t_here_queue *queue, t_here_queue_item item)
{
	if (queue == NULL)
		return (error(ERR_NULL_ARGS));
	if (!vector_push(queue, &item))
		return (error_sys());
	return (error(ERR_NO));
}

void	here_queue_clean(t_here_queue *queue)
{
	size_t	i;

	i = 0;
	while (i < queue->len)
	{
		free(((t_here_queue_item *)queue->data)[i].path);
		buff_free(&((t_here_queue_item *)queue->data)[i].delim);
		((t_here_queue_item *)queue->data)[i].path = NULL;
		((t_here_queue_item *)queue->data)[i].delim = (t_buff){0};
		((t_here_queue_item *)queue->data)[i].mode = NORMAL;
		++i;
	}
	queue->len = 0;
}

t_error	here_queue_get(t_here_queue *queue, t_here_queue_item *item, size_t i)
{
	if (queue->len == 0)
		return (error(ERR_EMPTY_STACK));
	else if (i >= queue->len)
		return (error(ERR_INDEX_OUT_OF_BOUND));
	return (*item = ((t_here_queue_item *)queue->data)[i], error(ERR_NO));
}
