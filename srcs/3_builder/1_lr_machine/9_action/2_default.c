#include "builder.h"
#include "action.h"
#include <stdlib.h>

// ERR_NO / ERR_LIBC
static t_error	malloc_action_table(t_lr_machine *machine)
{
	size_t	rows;
	size_t	cols;
	size_t	i;
	size_t	j;

	rows = machine->lr_states.len;
	cols = SYM_TERMINAL_MAX + 1;
	machine->actions = malloc(rows * sizeof(*machine->actions));
	if (!machine->actions)
		return (ERR_LIBC);
	i = 0;
	while (i < rows)
	{
		machine->actions[i] = malloc(cols * sizeof(**machine->actions));
		if (!machine->actions[i])
		{
			j = 0;
			while (j < i)
				free(machine->actions[j++]);
			free(machine->actions);
			return (machine->actions = NULL, ERR_LIBC);
		}
		i++;
	}
	return (ERR_NO);
}

static void	action_set_error(t_lr_machine *machine)
{
	size_t		row;
	size_t		col;
	size_t		col_count;
	t_action	action;

	action.type = ACTION_ERROR;
	action.payload = ACTION_PAYLOAD_EMPTY;
	col_count = SYM_TERMINAL_MAX + 1;
	row = 0;
	while (row < machine->lr_states.len)
	{
		col = 0;
		while (col < col_count)
		{
			machine->actions[row][col] = action;
			col++;
		}
		row++;
	}
}

t_error	action_build_default_table(t_lr_machine *machine)
{
	t_error	error;

	error = malloc_action_table(machine);
	if (error != ERR_NO)
		return (error);
	action_set_error(machine);
	return (ERR_NO);
}
