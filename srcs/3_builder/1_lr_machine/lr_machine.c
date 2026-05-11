#include "builder.h"
#include "rules__pub.h"
#include "symbols.h"
#include "first.h"
#include "lr_state.h"
#include "transition.h"
#include "action.h"
#include "goto.h"
#include <stdlib.h>
# include <locale.h>	// TODO: tmp debug
# include <stdio.h>		// TODO: tmp debug

void	lr_machine_init(t_lr_machine *machine)
{
	rules_init(machine->rules);
	lr_state_table_init(&machine->lr_states);
	transition_init(&machine->transitions);
	action_init(&machine->actions);
	goto_init(&machine->gotos);
}

static t_error	lr_machine_error(t_error error)
{
	error_print(NULL, "unable to build parsing tables", error);
	return (error);
}

// TODO: ERR_NO / ERR_LR_STATE_NOT_FOUND / ERR_LIBC [TODO...]
t_error	lr_machine_build(t_lr_machine *machine)
{
	t_error	error;

	setlocale(LC_NUMERIC, "de_DE");
	printf("-------------------------------------\n");
	printf("===> [lr_machine_build]\n");
	rules_build(machine->rules);
	printf("-> rules table built            (entries: %'6i)\n", RULE_COUNT);
	symbols_build_nullables_table(machine);
	printf("-> nullable symbols table built (entries: %'6i)\n", SYM_COUNT);
	first_build_table(machine);
	printf("-> first table built            (entries: %'6i)\n", SYM_COUNT * (SYM_TERMINAL_MAX + 1));
	error = transition_build_table(machine);
	if (error != ERR_NO)
		return (lr_machine_error(error));
	printf("-> transitions table built      (entries: %'6zu)\n", machine->transitions.len);
	printf("-> lr_states table built        (entries: %'6zu)\n", machine->lr_states.len);
	error = goto_build_table(machine);
	if (error != ERR_NO)
		return (lr_machine_error(error));
	printf("-> gotos table built            (entries: %'6zu)\n", machine->lr_states.len * (SYM_NON_TERMINAL_MAX - SYM_NON_TERMINAL_MIN + 1));
	error = action_build_table(machine);
	if (error != ERR_NO)
		return (lr_machine_error(error));
	printf("-> actions table built          (entries: %'6zu)\n", machine->lr_states.len * (SYM_TERMINAL_MAX + 1));
	printf("===> [lr_machine_build]\n");
	printf("-------------------------------------\n\n");
	return (setlocale(LC_NUMERIC, ""), ERR_NO);
}

void	lr_machine_free(t_lr_machine *machine)
{
	transition_free(&machine->transitions);
	action_free(machine->lr_states.len, &machine->actions);
	goto_free(machine->lr_states.len, &machine->gotos);
	lr_state_table_free(&machine->lr_states);
}
