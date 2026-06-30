#include <stdio.h>
#include <stdlib.h>
#include <readline/history.h>
#include "history_list_.h"
#include "history_readline_.h"
# include "logs.h"	// DEBUG

t_error	history_rl_add(t_history_rl *state, t_history_list *list, size_t count)
{
	ssize_t			i;
	const t_string	*entry;
	ssize_t			entries_to_add;

	if (count == 0)
		return (state->err);
	entries_to_add = history_rl_to_add_count(state, count);
	if (entries_to_add < 0)
	{
		history_rl_free(state);
		entries_to_add = -entries_to_add;
	}
	i = (ssize_t)list->len - entries_to_add;
	if (i < 0)
		i = 0;
	while ((size_t)i < list->len)
	{
		state->err = history_list_get(list, &entry, (size_t)i++);
		if (state->err.type)
			return (state->err);
		add_history(entry->data);
#ifdef DEBUG_HISTORY
		print_pass("[HISTORY] entry added = [%s]\n", entry->data);
#endif
		state->count++;
	}
	print_pass("entries uploaded to readline           %i\n", (int)state->count);
	return (state->err);
}
