#ifndef RULE_STATE_H
# define RULE_STATE_H

# include "parser.h"

bool		rule_state_equal(t_rule_state a, t_rule_state b);
bool		rule_state_is_complete(t_rule *rules, t_rule_state rule_state);
t_symbol	rule_state_next_symbol(t_rule *rules, t_rule_state rule_state);

#endif
