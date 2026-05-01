#include "lr_state.h"
#include "rule_state.h"

static bool	symbol_is_non_terminal(t_symbol symbol);
static bool	add_rules(
	t_lr_machine *machine,
	t_lr_state *lr_state,
	t_symbol symbol,
	bool *did_add);
static bool	lr_state_add(
	t_lr_state *lr_state,
	t_rule_state rule_state,
	bool *did_add);

bool	lr_state_complete(t_lr_machine *machine, t_lr_state *lr_state)
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
			next_symbol = rule_state_next_symbol(machine, rule_state);
			if (symbol_is_non_terminal(next_symbol))
				if (!add_rules(machine, lr_state, next_symbol, &did_add))
					return (false);
			i++;
		}
	}
	return (true);
}

static bool	symbol_is_non_terminal(t_symbol symbol)
{
	return (symbol >= SYM_NON_TERMINAL_MIN && symbol < SYM_NON_TERMINAL_MAX);
}

static bool	add_rules(
	t_lr_machine *machine,
	t_lr_state *lr_state,
	t_symbol symbol,
	bool *did_add)
{
	size_t			i;
	t_rule			rule;
	t_rule_state	rule_state;

	i = 0;
	while (i < RULE_COUNT)
	{
		rule = machine->rules[i];
		if (rule.lhs == symbol)
		{
			rule_state.rule_id = i;
			rule_state.pos = 0;
			if (!lr_state_add(lr_state, rule_state, did_add))
				return (false);
		}
		i++;
	}
	return (true);
}

static bool	lr_state_add(
	t_lr_state *lr_state,
	t_rule_state rule_state,
	bool *did_add)
{
	if (lr_state_contains(lr_state, rule_state))
		return (true);
	if (!vector_push(lr_state, &rule_state))
		return (false);
	*did_add = true;
	return (true);
}
