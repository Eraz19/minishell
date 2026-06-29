#include "history_readline_.h"

ssize_t	history_rl_to_add_count(t_history_rl *state, size_t count)
{
	if (state->max < 0)
		return ((ssize_t)count);
	if (count >= (size_t)state->max)
		return (-state->max);
	if (state->count > (size_t)state->max - count)
		return (-state->max);
	return ((ssize_t)count);
}
