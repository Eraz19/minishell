#include "lr_state.h"

static bool	build_initial_lr_state(t_rule *rules, t_lr_state *lr_states)
{
	t_rule_state	rule_state;
	t_lr_state		lr_state;

	lr_state_init(&lr_state);
	rule_state.rule_id = RULE_START_1;
	rule_state.pos = 0;
	if (!lr_state_add_rule_state(&lr_state, rule_state, NULL))
		return (lr_state_free(&lr_state), false);
	if (!lr_state_complete(rules, &lr_state))
		return (lr_state_free(&lr_state), false);
	if (!lr_state_add(lr_states, &lr_state, NULL))
		return (lr_state_free(&lr_state), false);
	return (true);
}

static bool	add_transition(t_lr_machine *machine, t_lr_state *from_lr_state, t_symbol symbol, t_lr_state *to_lr_state)
{
	t_transition	transition;
	size_t			from_id;
	size_t			to_id;

	if (!lr_state_find_id(&machine->lr_states, from_lr_state, &from_id))
		return (false);
	if (!lr_state_find_id(&machine->lr_states, to_lr_state, &to_id))
		return (false);
	transition.from_lr_state_id = from_id;
	transition.symbol = symbol;
	transition.to_lr_state_id = to_id;
	return (vector_push(&machine->transitions, &transition));
}

static bool	build_lr_state_and_transition(t_lr_machine *machine, t_lr_state *lr_state_from, t_symbol symbol)
{
	t_lr_state	lr_state_new;
	bool		did_add;

	if (!lr_state_next(machine->rules, &lr_state_new, lr_state_from, symbol))
		return (false);
	if (lr_state_new.len > 0)
	{
		did_add = false;
		if (!lr_state_add(&machine->lr_states, &lr_state_new, &did_add))
			return (lr_state_free(&lr_state_new), false);
		if (!add_transition(machine, lr_state_from, symbol, &lr_state_new))
		{
			if (!did_add)
				lr_state_free(&lr_state_new);
			return (false);
		}
		if (!did_add)
			lr_state_free(&lr_state_new);
	}
	return (true);
}

bool	transition_build_table(t_lr_machine *machine)
{
	size_t		i;
	t_symbol	symbol;
	t_lr_state	lr_state;

	if (!build_initial_lr_state(machine->rules, &machine->lr_states))
		return (false);
	i = 0;
	while (i < machine->lr_states.len)
	{
		lr_state = ((t_lr_state *)machine->lr_states.data)[i];
		symbol = 0;
		while (symbol < SYM_COUNT)
		{
			if (!build_lr_state_and_transition(machine, &lr_state, symbol))
				return (false);
			symbol++;
		}
		i++;
	}
	return (true);
}
