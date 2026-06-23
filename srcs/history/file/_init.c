#include <stdlib.h>
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

// TODO: use deserializer
t_error	history_file_load(t_history_file *state, t_history_list *list, ssize_t max)
{
	char	*entry;

	if (history_file_read(state).type)
		return (state->err);
	// TODO: reactivate when fixed
	(void)entry;
	(void)max;
	// while ((max >= 0 && list->len < (size_t)max) || max < 0)
	// {
	// 	if (history_file_extract(state, &entry).type)
	// 		return (state->err);
	// 	if (entry == NULL)
	// 		break ;
	// 	fprintf(stderr, "entry (%zu) = %s\n", list->len, entry);
	// 	state->err = history_list_insert(list, entry, 0);
	// 	if (state->err.type)
	// 		return (free(entry), state->err);
	// 	entry = NULL;
	// }
	return (state->loaded_count = list->len, state->err);
}
