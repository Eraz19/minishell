#include <stdio.h>
#include <stdlib.h>
#include <readline/history.h>
#include "history_list_.h"
#include "history_readline_.h"
# include "logs.h"	// DEBUG

t_error	history_rl_add(t_history_rl *state, t_history_list *list, size_t count)
{
	size_t			i;
	const t_string	*entry;

	if (count == 0)
		return (state->err);
	if (state->max < 0 || (size_t)state->max >= list->len)
		i = 0;
	else
		i = list->len - (size_t)state->max;	// history_rl_to_add_count(state, count);
	history_rl_free(state);
	while (i < list->len)
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
