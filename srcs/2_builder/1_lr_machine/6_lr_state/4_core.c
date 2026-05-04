#include "lr_state.h"
#include "rule_state.h"
#include "symbols.h"

static bool	add_rules(t_rule *rules, t_lr_state *lr_state, t_symbol symbol, bool *did_add)
{
	size_t			i;
	t_rule			rule;
	t_rule_state	rule_state;

	i = 0;
	while (i < RULE_COUNT)
	{
		rule = rules[i];
		if (rule.lhs == symbol)
		{
			rule_state.rule_id = i;
			rule_state.pos = 0;
			if (!lr_state_add_rule_state(lr_state, rule_state, did_add))
				return (false);
		}
		i++;
	}
	return (true);
}

bool	lr_state_complete(t_rule *rules, t_lr_state *lr_state)
{
	t_rule_state	rule_state;
	t_symbol		next_symbol;
	bool			did_add;
	size_t			i;

	did_add = true;
	while (did_add)
	{
		did_add = false;
		i = 0;
		while (i < lr_state->len)
		{
			rule_state = ((t_rule_state *)lr_state->data)[i];
			next_symbol = rule_state_next_symbol(rules, rule_state);
			if (symbol_is_non_terminal(next_symbol))
				if (!add_rules(rules, lr_state, next_symbol, &did_add))
					return (false);
			i++;
		}
	}
	return (true);
}

bool	lr_state_next(t_rule *rules, t_lr_state *dst, t_lr_state *src, t_symbol symbol)
{
	size_t			i;
	t_rule_state	rule_state;
	t_symbol		next_symbol;

	lr_state_init(dst);
	i = 0;
	while (i < src->len)
	{
		rule_state = ((t_rule_state *)src->data)[i];
		next_symbol = rule_state_next_symbol(rules, rule_state);
		if (next_symbol == symbol)
		{
			rule_state.pos++;
			if (!lr_state_add_rule_state(dst, rule_state, NULL))
				return (lr_state_free(dst), false);
		}
		i++;
	}
	if (dst->len > 0)
		if (!lr_state_complete(rules, dst))
			return (lr_state_free(dst), false);
	return (true);
}
