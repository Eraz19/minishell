#include <stdio.h>
#include <readline/readline.h>
#include "history_readline_.h"

void	history_rl_init(t_history_rl *state)
{
	state->count = 0;
}

void	history_rl_free(t_history_rl *state)
{
	rl_clear_history();
	state->count = 0;
}

t_error	history_rl_load(t_history_rl *state, t_history_list *list)
{
	return (history_rl_add(state, list, list->len));
}
