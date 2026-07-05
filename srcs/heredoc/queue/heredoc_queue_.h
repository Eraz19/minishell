#ifndef HEREDOC_QUEUE__H
# define HEREDOC_QUEUE__H

# include "heredoc.h"

void	heredoc_item_free(void *item);
void	heredoc_queue_init(t_heredoc_queue *queue);
void	heredoc_queue_free(t_heredoc_queue *queue);
t_error	heredoc_item_load(t_heredoc_item *item, const t_string *src, size_t *i);

// ============= MAIN FUNCTIONS ================

t_error	heredoc_queue_push(t_heredoc_queue *queue, t_heredoc_item item);
t_error	heredoc_queue_pop(t_heredoc_queue *queue, t_heredoc_item *item);

#endif
