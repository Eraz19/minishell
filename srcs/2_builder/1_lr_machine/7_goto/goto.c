#include "parser.h"
#include <limits.h>
#include <stdlib.h>

void	goto_init(size_t ***gotos)
{
	*gotos = NULL;
}

bool	goto_build_table(t_lr_machine *machine)
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
			// TODO
		}
		i++;
	}
}

bool	go_to(size_t **gotos, size_t current_lr_state_id, t_symbol symbol, size_t *new_lr_state_id)
{
	size_t	symbol_offset;
	size_t	tmp_lr_state_id;

	symbol_offset = symbol - SYM_NON_TERMINAL_MIN;
	tmp_lr_state_id = gotos[current_lr_state_id][symbol_offset];
	if (tmp_lr_state_id == SIZE_T_MAX)
		return (false);
	*new_lr_state_id = tmp_lr_state_id;
	return (true);
}

void	goto_free(size_t lr_states_count, size_t ***gotos)
{
	size_t	i;

	i = 0;
	while (i < lr_states_count)
	{
		free((*gotos)[i]);
		i++;
	}
	free(*gotos);
	*gotos = NULL;
}
