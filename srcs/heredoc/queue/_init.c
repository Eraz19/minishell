#include "heredoc_queue_.h"

void	heredoc_queue_init(t_heredoc_queue *queue)
{
	vector_init(queue, sizeof(t_heredoc_queue_item), 0);
}

void	heredoc_queue_free(t_heredoc_queue *queue)
{
	vector_free(queue, heredoc_queue_item_free);
}

void	heredoc_queue_item_free(void *item)
{
	t_heredoc_queue_item	*item_;

	item_ = (t_heredoc_queue_item *)item;
	string_free(&item_->path);
	string_free(&item_->delim);
	string_free(&item_->input);
	*item_ = (t_heredoc_queue_item){0};
}
