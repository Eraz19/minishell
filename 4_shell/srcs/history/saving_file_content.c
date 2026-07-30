#include <stdlib.h>
#include "utils.h"
#include "history.h"

t_error	history_prepare_entry(t_history *history, const t_string *entry)
{
	t_string	*file_content;
	t_string	serialized_entry;

	file_content = &history->file.content;
	history->err = serialize(entry->data, &serialized_entry);
	if (history->err.type)
		return (history->err);
	if (!string_append(file_content, &serialized_entry))
	{
		history->err = error_sys();
		return (string_free(&serialized_entry), history->err);
	}
	string_free(&serialized_entry);
	if (!string_append_n(file_content, "\n", 1))
		return (history->err = error_sys());
	return (history->err);
}

t_error	history_build_from_current(t_history *history)
{
	if (history->current_input.len == 0)
		return (history->err);
	else if (history->current_input.data[history->current_input.len - 1] == '\n')
	{
		history->current_input.data[history->current_input.len - 1] = '\0';
		history->current_input.len--;
		if (history->current_input.len == 0)
			return (history->err);
	}
	return (history_prepare_entry(history, &history->current_input));
}

t_error	history_build_from_list(t_history *history, size_t start)
{
	size_t			i;
	const t_string	*entry;

	i = start;
	while (i < history->list.len)
	{
		history_list_get(&history->list, &entry, i);
		if (history_prepare_entry(history, entry).type)
			return (history->err);
		i++;
	}
	return (history->err);
}

t_error	build_saving_file_content(t_history *history, size_t start)
{
	if (history_build_from_list(history, start).type)
		return (string_free(&history->file.content), history->err);
	if (history_build_from_current(history).type)
		return (string_free(&history->file.content), history->err);
	return (history->err);
}
