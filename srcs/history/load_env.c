#include <stdlib.h>
#include "params.h"
#include "history.h"

t_error	history_load_path_env(t_history *state)
{
	state->err = params_get_from_const("HISTFILE", &state->file.path);
	if (state->err.type == ERR_NO && state->file.path.len > 0)
		return (state->err);
	if (state->err.type && state->err.type != ERR_VAR_NOT_FOUND)
		return (state->err);
	state->err = params_get_from_const("HOME", &state->file.path);
	if (state->err.type == ERR_NO && state->file.path.len > 0)
	{
		if (!string_append_n(&state->file.path, "/.sh_history", -1))
			return (state->err = error_sys());
		return (state->err);
	}
	if (state->err.type && state->err.type != ERR_VAR_NOT_FOUND)
		return (state->err);
	(void)error_print(error(ERR_HISTORY_DISABLED),
		"history", "no valid history file path found", NULL, NULL);
	return (state->err = error(ERR_NO));
}

t_error	history_load_size_env(t_history *state)
{
	ssize_t		max;
	t_string	max_str;
	
	state->err = params_get_from_const("HISTSIZE", &max_str);
	if (state->err.type && state->err.type != ERR_VAR_NOT_FOUND)
		return (state->err);
	if (state->err.type == ERR_VAR_NOT_FOUND || max_str.len == 0)
		state->rl_history.max = -1;
	else
	{
		max = (ssize_t)ft_atol(max_str.data);
		string_free(&max_str);
		state->rl_history.max = max;
		if (max >= 0 && max < 128)
			state->rl_history.max = 128;
	}
	return (state->err = error(ERR_NO));
}
