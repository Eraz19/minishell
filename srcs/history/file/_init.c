#include <stdlib.h>
#include "utils.h"
#include "history_file_.h"

void	history_file_init(t_history_file *state)
{
	*state = (t_history_file){0};
}

void	history_file_free(t_history_file *state)
{
	free(state->content);
	*state = (t_history_file){0};
}

t_error	history_file_load(t_history_file *state, t_history_list *list, ssize_t max)
{
	size_t		i;
	char		*entry;
	t_vector	file_entries;

	if (history_file_read(state).type)
		return (state->err);
	state->err = deserialize_all(state->content, &file_entries);
	if (state->err.type)
		return (state->err);
	i = 0;
	while (file_entries.len > 0 && (max < 0 || i < (size_t)max))
	{
		if (!vector_remove(&file_entries, file_entries.len - 1, &entry))
		{
			state->err = error_sys();
			return (vector_free(&file_entries, free), state->err);
		}
		state->err = history_list_insert(list, entry, 0);
	 	if (state->err.type)
	 		return (vector_free(&file_entries, free), free(entry), state->err);
		entry = NULL;
		i++;
	}
	state->loaded_count = list->len;
	return (vector_free(&file_entries, free), state->err);
}
