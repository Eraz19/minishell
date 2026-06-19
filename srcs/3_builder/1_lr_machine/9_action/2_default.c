#include "builder.h"
#include "action.h"
#include <stdlib.h>

// ERR_LIBC
static t_error	action_save_error_and_free(t_lr_machine *machine, size_t count)
{
	t_error	err;
	size_t	j;

	err = error_sys();
	j = 0;
	while (j < count)
		free(machine->actions[j++]);
	free(machine->actions);
	machine->actions = NULL;
	return (err);
}

// ERR_NO / ERR_LIBC
static t_error	malloc_action_table(t_lr_machine *machine)
{
	size_t	rows;
	size_t	cols;
	size_t	i;

	rows = machine->lr_states.len;
	cols = SYM_TERMINAL_MAX + 1;
	machine->actions = malloc(rows * sizeof(*machine->actions));
	if (!machine->actions)
		return (error_sys());
	i = 0;
	while (i < rows)
	{
		machine->actions[i] = malloc(cols * sizeof(**machine->actions));
		if (!machine->actions[i])
			return (action_save_error_and_free(machine, i));
		i++;
	}
	return (error(ERR_NO));
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
	t_error	err;

	err = malloc_action_table(machine);
	if (err.type != ERR_NO)
		return (err);
	action_set_error(machine);
	return (error(ERR_NO));
}
