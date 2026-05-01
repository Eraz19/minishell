#ifndef RULE_STATE_H
# define RULE_STATE_H

# include "parser.h"

bool		rule_state_equal(t_rule_state a, t_rule_state b);
bool		rule_state_is_complete(t_lr_machine *machine, t_rule_state state);
t_symbol	rule_state_next_symbol(t_lr_machine *machine, t_rule_state state);

#endif
