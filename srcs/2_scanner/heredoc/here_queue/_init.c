/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 16:19:06 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/10 17:20:07 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "here_queue_.h"

void	here_queue_clean(void *item)
{
	t_here_queue_item	*item_;

	item_ = (t_here_queue_item *)item;
	free(item_->path);
	buff_free(&item_->delim);
	*item_ = (t_here_queue_item){0};
}

void	here_queue_init(t_here_queue *queue)
{
	*queue = (t_here_queue){0};
	vector_init(queue, sizeof(t_here_queue_item), 0);
}

void	here_queue_free(t_here_queue *queue)
{
	vector_free(queue, here_queue_clean);
	*queue = (t_here_queue){0};
}
