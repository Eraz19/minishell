/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_queue_.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 16:14:23 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/10 17:16:57 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_QUEUE__H
# define HERE_QUEUE__H

# include "types.h"
# include "libft.h"
# include "error.h"

typedef t_vector	t_here_queue;
typedef t_buff		t_heredoc_delim;

typedef enum e_heredoc_mode
{
	NORMAL,
	TAB_STRIP
}	t_heredoc_mode;

typedef struct s_here_queue_item
{
	t_file_path		path;
	t_heredoc_mode	mode;
	t_heredoc_delim	delim;
}	t_here_queue_item;

void	here_queue_clean(void *item);
void	here_queue_init(t_here_queue *queue);
void	here_queue_free(t_here_queue *queue);

t_error	here_queue_push(t_here_queue *queue, t_here_queue_item item);
t_error	here_queue_get(t_here_queue *queue, t_here_queue_item *item, size_t i);

#endif
