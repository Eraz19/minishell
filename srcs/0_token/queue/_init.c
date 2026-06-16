/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 14:18:23 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/16 14:41:14 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

void	token_context_queue_init(t_token_context_queue *queue)
{
	vector_init(queue, sizeof(t_token_context_queue_item), 0);
}

void	token_context_queue_free(t_token_context_queue *queue)
{
	vector_free(queue, NULL);
}
