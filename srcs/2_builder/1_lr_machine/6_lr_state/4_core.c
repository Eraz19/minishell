#include "lr_state.h"
#include "rule_state.h"
#include "symbols.h"
#include "first.h"

static void	compute_first(t_lr_machine *machine, t_first_param *param, t_rule_state rule_state)
{
	t_rule	rule;

	rule = machine->rules[rule_state.rule_id];
	if (rule_state.pos >= rule.rhs_len)
	{
		param->symbols = NULL;
		param->count = 0;
	}
	else
	{
		param->symbols = rule.rhs + (rule_state.pos + 1);
		param->count = rule.rhs_len - (rule_state.pos + 1);
	}
	param->has_lookahead = true;
	param->lookahead = rule_state.lookahead;
	first(machine, param);
}

static bool	add_rule_state_vars(t_lr_state *lr_state, t_rule_state rule_state, t_first_param *first, bool *did_add)
{
	t_symbol	terminal;

	terminal = 0;
	while (terminal <= SYM_TERMINAL_MAX)
	{
		if (first->result[terminal] == true)
		{
			rule_state.lookahead = terminal;
			if (!lr_state_add_rule_state(lr_state, rule_state, did_add))
				return (false);
		}
		terminal++;
	}
	return (true);
}

static bool	compute_rule_state(t_lr_machine *machine, t_lr_state *lr_state, t_rule_state rule_state, bool *did_add)
{
	t_symbol		next_symbol;
	t_first_param	first_param;
	size_t			rule_id;
	t_rule			rule;

	next_symbol = rule_state_next_symbol(machine->rules, rule_state);
	if (!symbol_is_non_terminal(next_symbol))
		return (true);
	compute_first(machine, &first_param, rule_state);
	rule_id = 0;
	while (rule_id < RULE_COUNT)
	{
		rule = machine->rules[rule_id];
		if (rule.lhs != next_symbol)
		{
			rule_id++;
			continue ;
		}
		rule_state.rule_id = rule_id;
		rule_state.pos = 0;
		if (!add_rule_state_vars(lr_state, rule_state, &first_param, did_add))
			return (false);
		rule_id++;
	}
	return (true);
}

bool	lr_state_complete(t_lr_machine *machine, t_lr_state *lr_state)
{
	t_rule_state	rule_state;
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
			if (!compute_rule_state(machine, lr_state, rule_state, &did_add))
				return (false);
			i++;
		}
	}
	return (true);
}

bool	lr_state_next(t_lr_machine *machine, t_lr_state *dst, t_lr_state *src, t_symbol symbol)
{
	size_t			i;
	t_rule_state	rule_state;
	t_symbol		next_symbol;

	lr_state_init(dst);
	i = 0;
	while (i < src->len)
	{
		rule_state = ((t_rule_state *)src->data)[i++];
		next_symbol = rule_state_next_symbol(machine->rules, rule_state);
		if (next_symbol != symbol)
			continue ;
		rule_state.pos++;
		if (!lr_state_add_rule_state(dst, rule_state, NULL))
			return (lr_state_free(dst), false);
	}
	if (dst->len > 0)
		if (!lr_state_complete(machine, dst))
			return (lr_state_free(dst), false);
	return (true);
}
