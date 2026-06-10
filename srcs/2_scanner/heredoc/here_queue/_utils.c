/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 16:13:00 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/10 17:17:09 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "here_queue_.h"

t_error	here_queue_push(t_here_queue *queue, t_here_queue_item item)
{
	if (queue == NULL)
		return (ERR_NULL_ARGS);
	if (!vector_push(queue, &item))
		return (ERR_LIBC);
	return (ERR_NO);
}

t_error	here_queue_get(t_here_queue *queue, t_here_queue_item *item, size_t i)
{
	if (queue->len == 0)
		return (ERR_EMPTY_STACK);
	else if (i >= queue->len)
		return (ERR_INDEX_OUT_OF_BOUND);
	return (*item = ((t_here_queue_item *)queue->data)[i], ERR_NO);
}
