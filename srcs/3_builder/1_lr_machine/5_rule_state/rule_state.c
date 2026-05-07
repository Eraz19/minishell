#include "builder.h"

bool	rule_state_equal(t_rule_state a, t_rule_state b)
{
	if (a.rule_id != b.rule_id)
		return (false);
	if (a.pos != b.pos)
		return (false);
	if (a.lookahead != b.lookahead)
		return (false);
	return (true);
}

bool	rule_state_is_complete(t_rule *rules, t_rule_state rule_state)
{
	return (rule_state.pos >= rules[rule_state.rule_id].rhs_len);
}

t_symbol	rule_state_next_symbol(t_rule *rules, t_rule_state rule_state)
{
	if (rule_state_is_complete(rules, rule_state))
		return (SYM_error);
	return (rules[rule_state.rule_id].rhs[rule_state.pos]);
}
