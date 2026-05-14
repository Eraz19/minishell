#include "builder.h"
#include "action_priv.h"

// TODO: tmp debug (always return ERR_LR_CONFLICT)
static t_error	print_conflict(t_action *action, size_t lr_state_id, t_symbol symbol, t_action_type target_type, size_t target_payload)
{
	t_buff	buff;
	char	*format_string;

	buff_init(&buff, 0, NULL, -1);
	if (action->type == ACTION_SHIFT)
		buff_append(&buff, " SHIFT-", -1);
	else if (action->type == ACTION_REDUCE)
		buff_append(&buff, " REDUCE-", -1);
	else if (action->type == ACTION_ACCEPT)
		buff_append(&buff, " ACCEPT-", -1);
	if (target_type == ACTION_SHIFT)
		buff_append(&buff, "SHIFT", -1);
	else if (target_type == ACTION_REDUCE)
		buff_append(&buff, "REDUCE", -1);
	else if (target_type == ACTION_ACCEPT)
		buff_append(&buff, "ACCEPT", -1);
	buff_append(&buff, " for lr_state %i and symbol %i (current payload = %i vs target = %i)", -1);
	format_string = buff_get_string(&buff);
	fprint_err(false, "⚠️ conflict", format_string,
		(int)lr_state_id, (int)symbol,
		(int)action->payload, (int)target_payload);
	return (ERR_LR_CONFLICT);
}

// ERR_NO / ERR_LR_CONFLICT
static t_error	add_shifts(t_lr_machine *machine)
{
	size_t			i;
	t_transition	transition;
	size_t			lr_state_id;
	t_symbol		symbol;
	t_action		*action;

	i = 0;
	while (i < machine->transitions.len)
	{
		transition = ((t_transition *)machine->transitions.data)[i];
		lr_state_id = transition.from_lr_state_id;
		symbol = transition.symbol;
		if (symbol <= SYM_TERMINAL_MAX)
		{
			action = &machine->actions[lr_state_id][symbol];
			if (action->type != ACTION_ERROR)
				return (print_conflict(action, lr_state_id, symbol, ACTION_SHIFT, transition.to_lr_state_id));
			action->type = ACTION_SHIFT;
			action->payload = transition.to_lr_state_id;
		}
		i++;
	}
	return (ERR_NO);
}

// ERR_NO / ERR_LR_CONFLICT
static t_error	add_reduces(
	t_lr_machine *machine,
	size_t lr_state_id,
	t_rule_state rule_state)
{
	t_symbol	symbol;
	t_action	*action;

	symbol = rule_state.lookahead;
	action = &machine->actions[lr_state_id][symbol];
	if (action->type != ACTION_ERROR)
		return (print_conflict(action, lr_state_id, symbol, ACTION_REDUCE, rule_state.rule_id));
	action->type = ACTION_REDUCE;
	action->payload = rule_state.rule_id;
	return (ERR_NO);
}

// ERR_NO / ERR_LR_CONFLICT
static bool	add_reduces_and_accept(
	t_lr_machine *machine,
	size_t lr_state_id,
	t_rule_state rule_state)
{
	t_rule		rule;
	t_action	*action;

	rule = machine->rules[rule_state.rule_id];
	if (rule_state.pos < rule.rhs_len)
		return (ERR_NO);
	if (rule_state.rule_id == RULE_START_1 && rule_state.lookahead == SYM_EOF)
	{
		action = &machine->actions[lr_state_id][SYM_EOF];
		if (action->type != ACTION_ERROR)
			return (print_conflict(action, lr_state_id, SYM_EOF, ACTION_ACCEPT, rule_state.rule_id));
		action->type = ACTION_ACCEPT;
		action->payload = rule_state.rule_id;
		return (ERR_NO);
	}
	return (add_reduces(machine, lr_state_id, rule_state));
}

// ERR_NO / ERR_LR_CONFLICT
static t_error	compute_rule_states(t_lr_machine *machine, size_t lr_state_id)
{
	t_lr_state		lr_state;
	size_t			rule_state_id;
	t_rule_state	rule_state;
	t_error			error;

	lr_state = ((t_lr_state *)machine->lr_states.data)[lr_state_id];
	rule_state_id = 0;
	while (rule_state_id < lr_state.len)
	{
		rule_state = ((t_rule_state *)lr_state.data)[rule_state_id];
		error = add_reduces_and_accept(machine, lr_state_id, rule_state);
		if (error != ERR_NO)
			return (error);
		rule_state_id++;
	}
	return (ERR_NO);
}

t_error	action_build_table(t_lr_machine *machine)
{
	size_t			lr_state_id;
	t_error			error;

	error = action_build_default_table(machine);
	if (error == ERR_NO)
		error = add_shifts(machine);
	if (error != ERR_NO)
		return (error);
	lr_state_id = 0;
	while (lr_state_id < machine->lr_states.len)
	{
		error = compute_rule_states(machine, lr_state_id);
		if (error != ERR_NO)
			return (error);
		lr_state_id++;
	}
	return (ERR_NO);
}
