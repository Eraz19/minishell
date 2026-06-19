#include "lr_state.h"

// ERR_NO / ERR_LIBC
static t_error	build_initial_lr_state(
	t_lr_machine *machine,
	t_lr_state *lr_states)
{
	t_rule_state	rule_state;
	t_lr_state		lr_state;
	t_error			err;

	lr_state_init(&lr_state);
	rule_state.rule_id = RULE_START_1;
	rule_state.pos = 0;
	rule_state.lookahead = SYM_EOF;
	err = lr_state_add_rule_state(&lr_state, rule_state, NULL);
	if (err.type != ERR_NO)
		return (lr_state_free(&lr_state), err);
	err = lr_state_complete(machine, &lr_state);
	if (err.type != ERR_NO)
		return (lr_state_free(&lr_state), err);
	err = lr_state_add(lr_states, &lr_state, NULL);
	if (err.type != ERR_NO)
		return (lr_state_free(&lr_state), err);
	return (error(ERR_NO));
}

// ERR_NO / ERR_LR_STATE_NOT_FOUND / ERR_LIBC
static t_error	add_transition(
	t_lr_machine *machine,
	t_lr_state *from_lr_state,
	t_symbol symbol,
	t_lr_state *to_lr_state)
{
	t_transition	transition;
	size_t			from_id;
	size_t			to_id;

	if (!lr_state_find_id(&machine->lr_states, from_lr_state, &from_id))
		return (error(ERR_LR_STATE_NOT_FOUND));
	if (!lr_state_find_id(&machine->lr_states, to_lr_state, &to_id))
		return (error(ERR_LR_STATE_NOT_FOUND));
	transition.from_lr_state_id = from_id;
	transition.symbol = symbol;
	transition.to_lr_state_id = to_id;
	if (!vector_push(&machine->transitions, &transition))
		return (error_sys());
	return (error(ERR_NO));
}

// ERR_NO / ERR_LR_STATE_NOT_FOUND / ERR_LIBC
static t_error	build_lr_state_and_transition(
	t_lr_machine *machine,
	t_lr_state *lr_state_from,
	t_symbol symbol)
{
	t_lr_state	lr_state_new;
	bool		did_add;
	t_error		err;

	err = lr_state_next(machine, &lr_state_new, lr_state_from, symbol);
	if (err.type != ERR_NO)
		return (err);
	if (lr_state_new.len > 0)
	{
		did_add = false;
		err = lr_state_add(&machine->lr_states, &lr_state_new, &did_add);
		if (err.type != ERR_NO)
			return (lr_state_free(&lr_state_new), err);
		err = add_transition(machine, lr_state_from, symbol, &lr_state_new);
		if (err.type != ERR_NO)
		{
			if (!did_add)
				lr_state_free(&lr_state_new);
			return (err);
		}
		if (!did_add)
			lr_state_free(&lr_state_new);
	}
	return (error(ERR_NO));
}

t_error	transition_build_table(t_lr_machine *machine)
{
	size_t		i;
	t_symbol	symbol;
	t_lr_state	lr_state;
	t_error		err;

	err = build_initial_lr_state(machine, &machine->lr_states);
	if (err.type != ERR_NO)
		return (err);
	i = 0;
	while (i < machine->lr_states.len)
	{
		lr_state = ((t_lr_state *)machine->lr_states.data)[i];
		symbol = 0;
		while (symbol < SYM_COUNT)
		{
			err = build_lr_state_and_transition(machine, &lr_state, symbol);
			if (err.type != ERR_NO)
				return (err);
			symbol++;
		}
		i++;
	}
	return (error(ERR_NO));
}
