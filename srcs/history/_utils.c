#include <stdlib.h>
#include "utils.h"
#include "history.h"

static t_error	history_prepare_entry(
	t_history *state,
	t_buff *content,
	char *entry)
{
	char 	*serial_entry;

	state->err = serialize(entry, &serial_entry);
	if (state->err.type)
		return (free(entry), state->err);
	if (!buff_append(content, serial_entry, (long)str_len(serial_entry)))
		return (free(serial_entry), free(entry), state->err = error_sys());
	if (!buff_append(content, "\n", 1))
		return (free(serial_entry), free(entry), state->err = error_sys());
	return (free(serial_entry), serial_entry = NULL, state->err);
}

static t_error	history_build_from_current(t_history *state, t_buff *content)
{
	char	*entry;

	if (state->current_input.len != 0)
	{
		if (state->current_input.data[state->current_input.len - 1] == '\n')
			state->current_input.len--;
		entry = buff_get_string(&state->current_input);
		if (entry == NULL)
			return (error_sys());
		if (history_prepare_entry(state, content, entry).type)
			return (free(entry), state->err);
		free(entry);
	}
	return (state->err);
}

static t_error	history_build_from_list(
	t_history *state,
	t_buff *content,
	size_t start)
{
	size_t	i;
	char	*entry;

	i = start;
	while (i < state->list.len)
	{
		state->err = history_list_get(&state->list, &entry, i);
		if (state->err.type)
			return (state->err);
		if (history_prepare_entry(state, content, entry).type)
			return (free(entry), state->err);
		free(entry);
		entry = NULL;
		i++;
	}
	return (state->err);
}

t_error	history_build_file_content(t_history *state, size_t start)
{
	t_buff	content;

	free(state->file.content);
	buff_init(&content, 0, NULL, 0);
	if (history_build_from_list(state, &content, start).type)
		return (buff_free(&content), state->err);
	if (history_build_from_current(state, &content).type)
		return (buff_free(&content), state->err);
	state->file.content = buff_get_string(&content);
	if (state->file.content == NULL)
		return (buff_free(&content), state->err = error_sys());
	return (buff_free(&content), state->err);
}
