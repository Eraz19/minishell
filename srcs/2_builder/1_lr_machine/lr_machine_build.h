#ifndef LR_MACHINE_BUILD_H
# define LR_MACHINE_BUILD_H

# include "parser.h"

/* ************************************************************************* */
/*                                  HELPERS                                  */
/* ************************************************************************* */

// id can be NULL
bool	lr_machine_find_lr_state_id(t_lr_machine *machine, t_lr_state *lr_state, size_t *id);
// did_add can be NULL, if not, it must already be initialized by caller
bool	lr_machine_add_lr_state(t_lr_machine *machine, t_lr_state *lr_state, bool *did_add);
bool	lr_machine_add_transition(t_lr_machine *machine, t_lr_state *from_lr_state, t_symbol symbol, t_lr_state *to_lr_state);

/* ************************************************************************* */
/*                                   CORE                                    */
/* ************************************************************************* */

bool	lr_machine_build_lr_states_and_transitions(t_lr_machine *machine);
bool	lr_machine_build_actions(t_lr_machine *machine);
bool	lr_machine_build_gotos(t_lr_machine *machine);

#endif
