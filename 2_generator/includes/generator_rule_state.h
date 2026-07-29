#ifndef GENERATOR_RULE_STATE_H
# define GENERATOR_RULE_STATE_H

# include "grammar_rules.h"
# include "grammar_rule_state.h"
# include <stdbool.h>

bool		rule_state_equal(const t_rule_state *a, const t_rule_state *b);
bool		rule_state_is_complete(
				const t_rule *rules,
				const t_rule_state *rule_state);
t_symbol	rule_state_next_symbol(
				const t_rule *rules,
				const t_rule_state *rule_state);

#endif
