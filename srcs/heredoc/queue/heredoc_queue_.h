#ifndef HEREDOC_QUEUE__H
# define HEREDOC_QUEUE__H

# include "heredoc.h"

void	heredoc_queue_item_free(void *item);
void	heredoc_queue_init(t_heredoc_queue *queue);
void	heredoc_queue_free(t_heredoc_queue *queue);

// ============= MAIN FUNCTIONS ================

t_error	heredoc_queue_push(t_heredoc_queue *queue, t_heredoc_queue_item item);
t_error	heredoc_queue_pop(t_heredoc_queue *queue, t_heredoc_queue_item *item);

#endif
