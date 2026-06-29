#include <stdlib.h>
#include "history_list_.h"

void	history_list_clean(void *item)
{
	char	*str;

	str = *(char **)item;
	if (str)
		free(str);
}

void	history_list_init(t_history_list *list)
{
	vector_init(list, sizeof(char *), 0);
}

void	history_list_free(t_history_list *list)
{
	vector_free(list, history_list_clean);
}
