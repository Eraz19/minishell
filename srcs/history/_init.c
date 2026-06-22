#include "error.h"
#include "history_.h"

void	history_init(t_history *state)
{
	*state = (t_history){0};
	history_list_init(&state->list);
	history_file_init(&state->file);
	history_rl_init(&state->rl_history);
	buff_init(&state->current_input, 0, NULL, 0);
}

void	history_free(t_history *state)
{
	history_list_free(&state->list);
	history_file_free(&state->file);
	buff_free(&state->current_input);
	history_rl_free(&state->rl_history);
	*state = (t_history){0};
}

t_error	history_load(t_history *state)
{
	ssize_t	max;

	if (history_load_path_env(state).type)
		return (state->err);
	print_pass("history_load_path_env()\n");
	if (history_load_size_env(state).type)
		return (state->err);
	max = state->rl_history.max;
	print_pass("history_load_size_env()\n");
	print_warn("rl_history.max = %i\n", (int)state->rl_history.max);
	print_warn("file.path = %s\n", state->file.path);
	if (history_file_load(&state->file, &state->list, max).type)
		return (state->err = state->file.err);
	print_pass("history_file_load()\n");
	print_warn("list.len = %i\n", (int)state->list.len);
	for (size_t i = 0; i < state->list.len; i++)
	{
		print_warn("%s\n", ((char **)state->list.data)[i]);
	}
	print_warn("file.path = %s\n", state->file.path);
	if (history_rl_load(&state->rl_history, &state->list).type)
		return (state->err = state->rl_history.err);
	return (state->err);
}
