#include "shell.h"
#include <stdlib.h>
#include "error.h"
#include "history.h"
#include "history_.h"
# include "logs.h"

t_error	history_save_entry(void)
{
	t_history	*state;
	
	print_title("%s()", __func__);
	state = shell_get_history();
	if (state == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	if (state->current_input.len == 0)
		return (state->err);
	print_warn("current_input before removing nl = [%s]\n", state->current_input.data);
	if (state->current_input.data[state->current_input.len - 1] == '\n')
	{
		state->current_input.data[state->current_input.len - 1] = '\0';
		state->current_input.len--;
	}
	print_warn("current_input after removing nl = [%s]\n", state->current_input.data);
	if (state->current_input.len == 0)
		return (state->err);
	state->err = history_list_push(&state->list, &state->current_input);
	if (state->err.type)
		return (state->err);
	string_init(&state->current_input, 0, NULL, 0);
	if (history_rl_add(&state->rl_history, &state->list, 1).type)
		return (state->err = state->rl_history.err);
	print_result("%s()", __func__);
	return (state->err);
}

t_error	history_append_to_entry(t_string *entry)
{
	t_history	*state;

	state = shell_get_history();
	if (state == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	if (!string_append(&state->current_input, entry))
		return (state->err = error_sys());
	return (state->err);
}

t_error	history_save(void)
{
	t_history	*state;

	print_title("%s()", __func__);
	state = shell_get_history();
	if (state == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	print_warn("history file path = \n%s\n", state->file.path.data);
	print_pass("list.len - file.loaded_count = %i\n", (int)state->list.len - (int)state->file.loaded_count);
	if (history_build_file_content(state, state->file.loaded_count).type)
		return (state->err);
	print_pass("file.content = \n%s\n", state->file.content.data);
	print_result("%s()", __func__);
	return (state->err = history_file_write(&state->file));
}
