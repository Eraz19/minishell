/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 14:26:43 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/16 15:09:57 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_error	token_context_queue_pop(
	t_token_context_queue *queue,
	t_token_context_queue_item *item)
{
	if (!vector_remove(queue, 0, (void *)item))
		return (ERR_LIBC);
	return (ERR_NO);
}

t_error	token_context_queue_push(
	t_token_context_queue *queue,
	size_t start,
	size_t end,
	t_context context)
{
	t_token_context_queue_item	item;
	
	item.end = end;
	item.start = start;
	item.context = context;
	if (!vector_push(queue, &item))
		return (ERR_LIBC);
	return (ERR_NO);
}
