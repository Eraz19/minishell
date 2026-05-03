#include "parser.h"
#include "rules__pub.h"
#include "lr_state.h"
#include "transition.h"
#include "action.h"
#include "goto.h"
#include <stdlib.h>

void	lr_machine_init(t_lr_machine *machine)
{
	rules_init(machine->rules);
	lr_state_table_init(&machine->lr_states);
	transition_init(&machine->transitions);
	action_init(&machine->actions);
	goto_init(&machine->gotos);
}

bool	lr_machine_build(t_lr_machine *machine)
{
	rules_build(machine->rules);
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
	transition_free(&machine->transitions);
	action_free(machine->lr_states.len, &machine->actions);
	goto_free(machine->lr_states.len, &machine->gotos);
	lr_state_table_free(&machine->lr_states);
}
