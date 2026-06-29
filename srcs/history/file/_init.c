#include <stdlib.h>
#include "utils.h"
#include "history_file_.h"

void	history_file_init(t_history_file *state)
{
	*state = (t_history_file){0};
	(void)string_init(&state->path, 0, NULL, 0);
	(void)string_init(&state->content, 0, NULL, 0);
}

void	history_file_free(t_history_file *state)
{
	string_free(&state->path);
	string_free(&state->content);
	*state = (t_history_file){0};
}

static inline t_error	history_file_take_entry(
							t_history_file *state,
							t_history_list *list,
							t_vector *file_entries,
							size_t index)
{
	t_string	*entry;

	entry = &((t_string *)file_entries->data)[index];
	state->err = history_list_push(list, entry->data);
	if (state->err.type)
		return (state->err);
	entry->cap = 0;
	entry->len = 0;
	entry->data = NULL;
	return (state->err);
}

t_error	history_file_load(
			t_history_file *state,
			t_history_list *list,
			ssize_t max)
{
	t_vector	file_entries;
	size_t		index;

	if (history_file_read(state).type)
		return (state->err);
	if (state->content.len == 0)
		return (state->err);
	state->err = deserialize_all(state->content.data, &file_entries);
	if (state->err.type)
		return (state->err);
	if (max < 0 || (size_t)max >= file_entries.len)
		index = 0;
	else
		index = file_entries.len - (size_t)max;
	state->loaded_count = 0;
	while (index < file_entries.len)
	{
		if (history_file_take_entry(state, list, &file_entries, index).type)
			break ;
		index++;
		state->loaded_count++;
	}
	vector_free(&file_entries, string_free_void);
	return (state->err);
}
