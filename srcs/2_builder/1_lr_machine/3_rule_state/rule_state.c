#include "parser.h"

bool	rule_state_equal(t_rule_state a, t_rule_state b)
{
	return (a.rule_id == b.rule_id && a.pos == b.pos);
}

bool	rule_state_is_complete(t_lr_machine *machine, t_rule_state state)
{
	t_rule	*rule;

	rule = &machine->rules[state.rule_id];
	return (state.pos >= rule->rhs_len);
}

t_symbol	rule_state_next_symbol(t_lr_machine *machine, t_rule_state state)
{
	t_rule	*rule;

	if (rule_state_is_complete(machine, state))
		return (SYM_error);
	rule = &machine->rules[state.rule_id];
	return (rule->rhs[state.pos]);
}
