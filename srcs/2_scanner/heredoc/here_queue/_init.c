/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 16:19:06 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/04 18:38:43 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "_here_queue.h"

void	here_queue_init(t_here_queue *queue)
{
	*queue = (t_here_queue){0};
	vector_init(queue, sizeof(t_here_queue_item), 0);
}

void	here_queue_free(t_here_queue *queue)
{
	here_queue_clean(queue);
	vector_free(queue);
	*queue = (t_here_queue){0};
}
