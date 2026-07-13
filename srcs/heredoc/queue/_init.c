#include "heredoc_queue_.h"

void	heredoc_queue_init(t_heredoc_queue *queue)
{
	vector_init(queue, sizeof(t_heredoc_item), 0);
}

void	heredoc_queue_free(t_heredoc_queue *queue)
{
	vector_free(queue, heredoc_item_free);
}

void	heredoc_item_free(void *item)
{
	t_heredoc_item	*item_;

	item_ = (t_heredoc_item *)item;
	string_free(&item_->path);
	string_free(&item_->delim);
	string_free(&item_->input);
	*item_ = (t_heredoc_item){0};
}

t_error	heredoc_item_load(t_heredoc_item *item, const t_string *src, size_t i)
{
	if (src == NULL)
	{
		if (!string_init(&item->input, 1, "", -1))
			return (error_sys());
	}
	else
		if (!string_init(&item->input, 0, src->data, (long)src->len))
			return (error_sys());
	return (item->i = i, error(ERR_NO));
}
