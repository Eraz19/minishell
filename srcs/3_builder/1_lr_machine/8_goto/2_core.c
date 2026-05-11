#include "builder.h"
#include "goto.h"
#include <stdlib.h>

// ERR_NO / ERR_LIBC
static t_error	malloc_goto_table(t_lr_machine *machine)
{
	size_t	rows;
	size_t	cols;
	size_t	i;
	size_t	j;

	rows = machine->lr_states.len;
	cols = SYM_NON_TERMINAL_MAX - SYM_NON_TERMINAL_MIN + 1;
	machine->gotos = malloc(rows * sizeof(*machine->gotos));
	if (!machine->gotos)
		return (ERR_LIBC);
	i = 0;
	while (i < rows)
	{
		machine->gotos[i] = malloc(cols * sizeof(**machine->gotos));
		if (!machine->gotos[i])
		{
			j = 0;
			while (j < i)
				free(machine->gotos[j++]);
			free(machine->gotos);
			return (machine->gotos = NULL, ERR_LIBC);
		}
		i++;
	}
	return (ERR_NO);
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

bool	goto_build_table(t_lr_machine *machine)
{
	size_t			i;
	t_transition	transition;
	t_symbol		symbol;
	size_t			row;
	size_t			col;

	if (malloc_goto_table(machine) != ERR_NO)
		return (ERR_LIBC);
	goto_set_empty(machine);
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
	return (ERR_NO);
}

bool	go_to(
	size_t **gotos,
	size_t current_lr_state_id,
	t_symbol symbol,
	size_t *new_lr_state_id)
{
	size_t	symbol_offset;
	size_t	tmp_lr_state_id;

	if (symbol < SYM_NON_TERMINAL_MIN || symbol > SYM_NON_TERMINAL_MAX)
		return (false);
	symbol_offset = symbol - SYM_NON_TERMINAL_MIN;
	tmp_lr_state_id = gotos[current_lr_state_id][symbol_offset];
	if (tmp_lr_state_id == GOTO_EMPTY)
		return (false);
	*new_lr_state_id = tmp_lr_state_id;
	return (true);
}
