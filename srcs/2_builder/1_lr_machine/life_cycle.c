#include "parser.h"
#include "rules__pub.h"
#include "lr_state.h"
#include "lr_machine_build.h"
#include <stdlib.h>

void	lr_machine_init(t_lr_machine *machine)
{
	rules_init(machine->rules);
	vector_init(&machine->lr_states, sizeof(t_lr_state), 0);
	vector_init(&machine->transitions, sizeof(t_transition), 0);
	machine->actions = NULL;
	machine->gotos = NULL;
}

bool	lr_machine_build(t_lr_machine *machine)
{
	if (!transition_build_table(machine))
		return (false);
	if (!action_build_table(machine))
		return (false);
	if (!goto_build_table(machine))
		return (false);
	return (true);
}

void	lr_machine_free(t_lr_machine *machine)
{
	size_t	i;

	vector_free(&machine->transitions);
	if (machine->actions)
	{
		i = 0;
		while (i < machine->lr_states.len)
			free(machine->actions[i++]);
		free(machine->actions);
	}
	if (machine->gotos)
	{
		i = 0;
		while (i < machine->lr_states.len)
			free(machine->gotos[i++]);
		free(machine->gotos);
	}
	i = 0;
	while (i < machine->lr_states.len)
	{
		lr_state_free(&((t_lr_state *)machine->lr_states.data)[i]);
		i++;
	}
	vector_free(&machine->lr_states);
}
