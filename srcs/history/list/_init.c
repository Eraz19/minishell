#include "history_list_.h"

void	history_list_clean(void *item)
{
	string_free(item);
}

void	history_list_init(t_history_list *list)
{
	vector_init(list, sizeof(t_string), 0);
}

void	history_list_free(t_history_list *list)
{
	vector_free(list, history_list_clean);
}
