#include "lr_machine_build.h"
#include "lr_state.h"
#include <limits.h>


/*---------------- TODO ----------------*/

bool	actions_build(t_lr_machine *machine)
{
	// TODO
}

bool	gotos_build(t_lr_machine *machine)
{
	size_t			i;
	t_transition	transition;
	t_symbol		symbol;

	i = 0;
	while (i < machine->transitions.len)
	{
		transition = ((t_transition *)machine->transitions.data)[i];
		symbol = transition.symbol;
		if (symbol >= SYM_NON_TERMINAL_MIN)
		{
			
		}
		i++;
	}
}

bool	go_to(t_lr_machine *machine, size_t current_lr_state_id, t_symbol symbol, size_t *new_lr_state_id)
{
	size_t	symbol_offset;
	size_t	tmp_lr_state_id;

	symbol_offset = symbol - SYM_NON_TERMINAL_MIN;
	tmp_lr_state_id = machine->gotos[current_lr_state_id][symbol_offset];
	if (tmp_lr_state_id == SIZE_T_MAX)
		return (false);
	*new_lr_state_id = tmp_lr_state_id;
	return (true);
}
