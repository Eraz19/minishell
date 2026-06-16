/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 16:19:06 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/12 18:03:45 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "heredoc_queue_.h"

void	heredoc_queue_item_free(void *item)
{
	t_heredoc_queue_item	*item_;

	item_ = (t_heredoc_queue_item *)item;
	free(item_->path);
	free(item_->delim);
	*item_ = (t_heredoc_queue_item){0};
}

void	heredoc_queue_init(t_heredoc_queue *queue)
{
	vector_init(queue, sizeof(t_heredoc_queue_item), 0);
}

void	heredoc_queue_free(t_heredoc_queue *queue)
{
	vector_free(queue, heredoc_queue_item_free);
}
