#include <stdlib.h>
#include "history_.h"
#include "history_list_.h"

t_error	history_list_push(t_history_list *list, char *item)
{
	if (!vector_push(list, &item))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	history_list_insert(t_history_list *list, char *item, size_t index)
{
	if (!vector_insert(list, index, &item))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	history_list_get(t_history_list *list, char **item, size_t i)
{
	t_error	err;
	char	*item_;

	if (list->len == 0)
		return (error(ERR_EMPTY_STACK));
	else if (i >= list->len)
		return (error(ERR_INDEX_OUT_OF_BOUND));
	item_ = str_dup(((char **)list->data)[i]);
	if (item_ == NULL)
		return (error_sys());
	err = history_entry_serialize(&item_);
	if (err.type)
		return (free(item_), err);
	return (*item = item_, error(ERR_NO));
}
