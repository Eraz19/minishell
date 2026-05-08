#include "builder.h"
#include "rules__pub.h"
#include "symbols.h"
#include "first.h"
#include "lr_state.h"
#include "transition.h"
#include "action.h"
#include "goto.h"
#include <stdlib.h>
#include <locale.h>
# include <stdio.h>	// TODO: tmp debug

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
	setlocale(LC_NUMERIC, "de_DE");
	printf("lr_machine_build: START\n");
	rules_build(machine->rules);
	printf("lr_machine_build: rules table built            (entries: %'6i)\n", RULE_COUNT);
	symbols_build_nullables_table(machine);
	printf("lr_machine_build: nullable symbols table built (entries: %'6i)\n", SYM_COUNT);
	first_build_table(machine);
	printf("lr_machine_build: first table built            (entries: %'6i)\n", SYM_COUNT * (SYM_TERMINAL_MAX + 1));
	if (!transition_build_table(machine))
		return (false);
	printf("lr_machine_build: transitions table built      (entries: %'6zu)\n", machine->transitions.len);
	printf("lr_machine_build: lr_states table built        (entries: %'6zu)\n", machine->lr_states.len);
	if (!goto_build_table(machine))
		return (false);
	printf("lr_machine_build: gotos table built            (entries: %'6zu)\n", machine->lr_states.len * (SYM_NON_TERMINAL_MAX - SYM_NON_TERMINAL_MIN + 1));
	if (!action_build_table(machine))
		return (false);
	printf("lr_machine_build: actions table built          (entries: %'6zu)\n", machine->lr_states.len * (SYM_TERMINAL_MAX + 1));
	printf("lr_machine_build: DONE\n");
	setlocale(LC_NUMERIC, "");
	return (true);
}

void	lr_machine_free(t_lr_machine *machine)
{
	transition_free(&machine->transitions);
	action_free(machine->lr_states.len, &machine->actions);
	goto_free(machine->lr_states.len, &machine->gotos);
	lr_state_table_free(&machine->lr_states);
}
