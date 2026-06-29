#include <stdlib.h>
#include "history_list_.h"

t_error	history_list_push(t_history_list *list, const t_string *item)
{
	if (!vector_push(list, item))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	history_list_get(t_history_list *list, const t_string **item, size_t i)
{
	if (list->len == 0)
		return (error(ERR_EMPTY_STACK));
	else if (i >= list->len)
		return (error(ERR_INDEX_OUT_OF_BOUND));
	*item = &((t_string *)list->data)[i];
	return (error(ERR_NO));
}
