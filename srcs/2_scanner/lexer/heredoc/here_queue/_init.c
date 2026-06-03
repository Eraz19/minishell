/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 16:19:06 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/03 15:13:24 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "_heredoc.h"

void	here_queue_init(t_here_queue *queue)
{
	if (queue == NULL)
		return ;
	*queue = (t_here_queue){0};
	vector_init(queue, sizeof(t_here_queue_item), 0);
}

void	here_queue_free(t_here_queue *queue)
{
	if (queue == NULL)
		return ;
	here_queue_clean(queue);
	vector_free(queue);
	*queue = (t_here_queue){0};
}
