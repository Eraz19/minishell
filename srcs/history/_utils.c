#include <stdlib.h>
#include "utils.h"
#include "history.h"
#include "history_.h"

static t_error	history_prepare_entry(
					t_history *state,
					t_string *content,
					char *entry)
{
	state->err = serialize(entry, content);
	if (state->err.type)
		return (state->err);
	if (!string_append_n(content, "\n", 1))
		return (state->err = error_sys());
	return (state->err);
}

static t_error	history_build_from_current(t_history *state, t_string *content)
{
	char	*entry;

	if (state->current_input.len == 0)
		return (state->err);
	else if (state->current_input.data[state->current_input.len - 1] == '\n')
	{
		state->current_input.len--;
		if (state->current_input.len == 0)
			return (state->err);
	}
	entry = buff_get_string(&state->current_input);
	if (entry == NULL)
		return (state->err = error_sys());
	if (history_prepare_entry(state, content, entry).type)
		return (free(entry), state->err);
	free(entry);
	return (state->err);
}

static t_error	history_build_from_list(
					t_history *state,
					t_string *content,
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
	if (history_build_from_list(state, &state->file.content, start).type)
		return (string_free(&state->file.content), state->err);
	if (history_build_from_current(state, &state->file.content).type)
		return (string_free(&state->file.content), state->err);
	return (state->err);
}
