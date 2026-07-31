#include "generator_actions_priv.h"
#include "grammar_symbols.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#define ACTION_TOO_BIG	"generator: actions table size overflow\n"

static inline bool	action_malloc_table(
						t_action **actions,
						size_t lr_states_count)
{
	ssize_t	osef;
	size_t	col_count;

	col_count = SYM_TERMINAL_MAX + 1;
	if (col_count > SIZE_MAX / sizeof(**actions)
		|| lr_states_count > SIZE_MAX / (col_count * sizeof(**actions)))
	{
		osef = write(STDERR_FILENO, ACTION_TOO_BIG, str_len(ACTION_TOO_BIG));
		(void)osef;
		return (false);
	}
	*actions = malloc(lr_states_count * col_count * sizeof(**actions));
	if (*actions == NULL)
		return (perror("generator"), false);
	return (true);
}

static inline void	action_set_error(t_action *actions, size_t lr_states_count)
{
	size_t		col_count;
	size_t		table_size;
	size_t		i;
	t_action	action;

	action.type = ACTION_ERROR;
	action.payload = ACTION_PAYLOAD_EMPTY;
	col_count = SYM_TERMINAL_MAX + 1;
	table_size = lr_states_count * col_count;
	i = 0;
	while (i < table_size)
		actions[i++] = action;
}

bool	action_build_default_table(t_action **actions, size_t lr_states_count)
{
	if (!action_malloc_table(actions, lr_states_count))
		return (false);
	action_set_error(*actions, lr_states_count);
	return (true);
}
