#include "goto.h"
#include "transition_type.h"
#include <stdlib.h>

// ERR_LIBC
static t_error	goto_save_error_and_free(t_lr_machine *machine, size_t count)
{
	t_error	err;
	size_t	j;

	err = error_sys();
	j = 0;
	while (j < count)
		free(machine->gotos[j++]);
	free(machine->gotos);
	machine->gotos = NULL;
	return (err);
}

// ERR_NO / ERR_LIBC
static t_error	malloc_goto_table(t_lr_machine *machine)
{
	size_t	rows;
	size_t	cols;
	size_t	i;

	rows = machine->lr_states.len;
	cols = SYM_NON_TERMINAL_MAX - SYM_NON_TERMINAL_MIN + 1;
	machine->gotos = malloc(rows * sizeof(*machine->gotos));
	if (!machine->gotos)
		return (error_sys());
	i = 0;
	while (i < rows)
	{
		machine->gotos[i] = malloc(cols * sizeof(**machine->gotos));
		if (!machine->gotos[i])
			return (goto_save_error_and_free(machine, i));
		i++;
	}
	return (error(ERR_NO));
}

static void	goto_set_empty(t_lr_machine *machine)
{
	size_t	row;
	size_t	col;
	size_t	col_count;

	col_count = SYM_NON_TERMINAL_MAX - SYM_NON_TERMINAL_MIN + 1;
	row = 0;
	while (row < machine->lr_states.len)
	{
		col = 0;
		while (col < col_count)
		{
			machine->gotos[row][col] = GOTO_EMPTY;
			col++;
		}
		row++;
	}
}

static void	goto_process_transitions(t_lr_machine *machine)
{
	size_t			i;
	t_transition	transition;
	t_symbol		symbol;
	size_t			row;
	size_t			col;

	i = 0;
	while (i < machine->transitions.len)
	{
		transition = ((t_transition *)machine->transitions.data)[i];
		symbol = transition.symbol;
		if (symbol >= SYM_NON_TERMINAL_MIN && symbol <= SYM_NON_TERMINAL_MAX)
		{
			row = transition.from_lr_state_id;
			col = symbol - SYM_NON_TERMINAL_MIN;
			machine->gotos[row][col] = transition.to_lr_state_id;
		}
		i++;
	}
}

t_error	goto_build_table(t_lr_machine *machine)
{
	t_error			err;

	err = malloc_goto_table(machine);
	if (err.type != ERR_NO)
		return (err);
	goto_set_empty(machine);
	goto_process_transitions(machine);
	return (error(ERR_NO));
}
