#include "history_list.h"

void	history_list_init(t_history_list *list)
{
	vector_init(list, sizeof(t_string), 0);
}

void	history_list_free(t_history_list *list)
{
	vector_free(list, (void *)string_free);
}

t_error	history_list_load(t_history_list *history_list, t_vector *entries, size_t start)
{
	size_t		i;
	t_error		err;
	t_string	*entry;

	i = start;
	while (i < entries->len)
	{
		entry = &((t_string *)entries->data)[i++];
		err = history_list_push(history_list, entry);
		if (err.type)
			return (err);
	}
	return (err);
}
