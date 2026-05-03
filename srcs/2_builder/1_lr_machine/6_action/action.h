#ifndef ACTION_H
# define ACTION_H

# include "parser.h"

void	action_init(t_action ***actions);
bool	action_build_table(t_lr_machine *machine);
void	action_free(size_t lr_states_count, t_action ***actions);

#endif
