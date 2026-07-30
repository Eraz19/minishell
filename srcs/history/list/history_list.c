#include <assert.h> // DEBUG
#include <stdlib.h>
#include "history_list.h"

t_error	history_list_push(t_history_list *list, const t_string *item)
{
	if (!vector_push(list, item))
		return (error_sys());
	return (error(ERR_NO));
}

void	history_list_get(t_history_list *list, const t_string **item, size_t i)
{
	assert(list->len > 0 && i < list->len);
	*item = &((t_string *)list->data)[i];
}
