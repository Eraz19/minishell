/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _here_queue.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 16:14:23 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/03 15:17:59 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __HERE_QUEUE_H
# define __HERE_QUEUE_H

# include "libft.h"
# include "error.h"

// Forward types
typedef struct s_here_queue_item	t_here_queue_item;

typedef t_vector					t_here_queue;
typedef t_buff						t_heredoc_delim;

void	here_queue_init(t_here_queue *queue);
void	here_queue_free(t_here_queue *queue);

void	here_queue_clean(t_here_queue *queue);
t_error	here_queue_push(t_here_queue *queue, t_here_queue_item item);
t_error	here_queue_get(t_here_queue *queue, t_here_queue_item *item, size_t i);

#endif
