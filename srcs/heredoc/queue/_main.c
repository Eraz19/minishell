#include "heredoc_queue_.h"

t_error	heredoc_queue_push(t_heredoc_queue *queue, t_heredoc_item item)
{
	if (!vector_push(queue, &item))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	heredoc_queue_pop(t_heredoc_queue *queue, t_heredoc_item *item)
{
	if (queue->len == 0)
		return (error(ERR_EMPTY_STACK));
	if (!vector_remove(queue, 0, item))
		return (error_sys());
	return (error(ERR_NO));
}
