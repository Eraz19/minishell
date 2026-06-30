#include "rules__pub.h"
#include "symbols.h"
#include "first.h"
#include "lr_state.h"
#include "transition.h"
#include "transition_type.h"
#include "action.h"
#include "goto.h"
#include <stdlib.h>
# include "logs.h"	// DEBUG

#define LR_MACHINE_ERROR_MESSAGE	"unable to build parsing tables"
#define TRANSITION_INITIAL_CAP		6000
#define LR_STATE_INITIAL_CAP		2000

void	lr_machine_init(t_lr_machine *machine)
{
	rules_init(machine->rules);
	lr_state_table_init(&machine->lr_states);
	transition_init(&machine->transitions);
	action_init(&machine->actions);
	goto_init(&machine->gotos);
}

static inline t_error	lr_machine_alloc_tables(t_lr_machine *machine)
{
	if (!vector_init(&machine->transitions, sizeof(t_transition),
		TRANSITION_INITIAL_CAP))
		return (error_sys());
	if (!vector_init(&machine->lr_states, sizeof(t_lr_state),
		LR_STATE_INITIAL_CAP))
		return (error_sys());
	return (error(ERR_NO));
}

static inline t_error	lr_machine_build_error(t_error err, const char *message)
{
	return (error_print(err, "lr_machine", message, NULL, NULL));
}

// TODO: ERR_NO / ERR_LR_STATE_NOT_FOUND / ERR_LIBC [TODO...]
t_error	lr_machine_build_tables(t_lr_machine *machine)
{
	t_error	err;

	print_title("lr_machine_build_tables()");
	rules_build(machine->rules);
	print_pass("rules table built                      (entries: %'6i)\n", RULE_COUNT);
	symbols_build_nullables_table(machine);
	print_pass("nullable symbols table built           (entries: %'6i)\n", SYM_COUNT);
	first_build_table(machine);
	print_pass("first table built                      (entries: %'6i)\n", SYM_COUNT * (SYM_TERMINAL_MAX + 1));
	err = lr_machine_alloc_tables(machine);
	if (err.type != ERR_NO)
		return (lr_machine_build_error(err, "unable to malloc tables"));
	err = transition_build_table(machine);
	if (err.type != ERR_NO)
		return (lr_machine_build_error(err, LR_MACHINE_ERROR_MESSAGE));
	print_pass("transitions table built                (entries: %'6zu)\n", machine->transitions.len);
	print_pass("lr_states table built                  (entries: %'6zu)\n", machine->lr_states.len);
	err = goto_build_table(machine);
	if (err.type != ERR_NO)
		return (lr_machine_build_error(err, LR_MACHINE_ERROR_MESSAGE));
	print_pass("gotos table built                      (entries: %'6zu)\n", machine->lr_states.len * (SYM_NON_TERMINAL_MAX - SYM_NON_TERMINAL_MIN + 1));
	err = action_build_table(machine);
	if (err.type != ERR_NO)
		return (lr_machine_build_error(err, LR_MACHINE_ERROR_MESSAGE));
	print_pass("actions table built                    (entries: %'6zu)\n", machine->lr_states.len * (SYM_TERMINAL_MAX + 1));
	print_result("lr_machine_build_tables()");
	return (error(ERR_NO));
}

void	lr_machine_free(t_lr_machine *machine)
{
	transition_free(&machine->transitions);
	action_free(machine->lr_states.len, &machine->actions);
	goto_free(machine->lr_states.len, &machine->gotos);
	lr_state_table_free(&machine->lr_states);
}
