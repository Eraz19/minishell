#include <stdlib.h>
#include "history_list_.h"

void	history_list_clean(void *item)
{
	char	*item_;

	item_ = (char *)item;
	if (item_ != NULL)
		free(item_);
}

void	history_list_init(t_history_list *list)
{
	*list = (t_history_list){0};
	vector_init(list, sizeof(char *), 0);
}

void	history_list_free(t_history_list *list)
{
	vector_free(list, history_list_clean);
	*list = (t_history_list){0};
}
