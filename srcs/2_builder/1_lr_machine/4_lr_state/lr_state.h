#ifndef LR_STATE_H
# define LR_STATE_H

# include "parser.h"

# define LR_STATE_INITIAL_CAP	16

bool	lr_state_init(t_lr_state *lr_state);
bool	lr_state_contains(t_lr_state *lr_state, t_rule_state rule_state);
// Completes an lr_state by adding all implied rule_states (aka closure in LR parsing theory)
bool	lr_state_complete(t_lr_machine *machine, t_lr_state *lr_state);
void	lr_state_free(t_lr_state *lr_state);

#endif
