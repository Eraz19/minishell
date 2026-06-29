#include "shell.h"
#include <stdlib.h>
#include "error.h"
#include "history.h"
#include "history_.h"

t_error	history_save_entry(void)
{
	char		*entry;
	t_history	*state;
	
	state = shell_get_history();
	if (state == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	if (state->current_input.len == 0)
		return (state->err);
	if (state->current_input.data[state->current_input.len - 1] == '\n')
		state->current_input.len--;
	if (state->current_input.len == 0)
		return (state->err);
	entry = buff_get_string(&state->current_input);
	if (entry == NULL)
		return (state->err = error_sys());
	state->err = history_list_push(&state->list, entry);
	if (state->err.type)
		return (free(entry), state->err);
	buff_free(&state->current_input);
	buff_init(&state->current_input, 0, NULL, 0);
	if (history_rl_add(&state->rl_history, &state->list, 1).type)
		return (state->err = state->rl_history.err);
	return (state->err);
}

t_error	history_append_to_entry(char *entry)
{
	t_history	*state;

	state = shell_get_history();
	if (state == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	if (!buff_append_n(&state->current_input, entry, -1))
		return (state->err = error_sys());
	return (state->err);
}

t_error	history_save(void)
{
	t_history	*state;

	state = shell_get_history();
	if (state == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	if (history_build_file_content(state, state->file.loaded_count).type)
		return (state->err);
	return (state->err = history_file_write(&state->file));
}
