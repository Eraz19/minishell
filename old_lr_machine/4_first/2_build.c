#include "first_priv.h"
#include "symbols.h"

static void	first_set_default_and_terminals(t_lr_machine *machine)
{
	t_symbol	symbol;
	t_symbol	terminal;

	symbol = 0;
	while (symbol < SYM_COUNT)
	{
		terminal = 0;
		while (terminal <= SYM_TERMINAL_MAX)
		{
			machine->first[symbol][terminal] = false;
			terminal++;
		}
		if (symbol <= SYM_TERMINAL_MAX)
			machine->first[symbol][symbol] = true;
		symbol++;
	}
}

static void	first_build_from_rule(t_lr_machine *machine, t_rule rule, bool *did_add)
{
	size_t		pos;
	t_symbol	symbol;

	pos = 0;
	while (pos < rule.rhs_len)
	{
		symbol = rule.rhs[pos++];
		if (symbol_is_terminal(symbol))
		{
			first_add(&machine->first[rule.lhs][symbol], did_add);
			return ;
		}
		first_add_list(
			machine->first[rule.lhs],
			machine->first[symbol],
			did_add);
		if (!symbol_is_nullable(machine, symbol))
			return ;
	}
}

void	first_build_table(t_lr_machine *machine)
{
	size_t		i;
	t_rule		rule;
	bool		did_add;

	first_set_default_and_terminals(machine);
	did_add = true;
	while (did_add)
	{
		did_add = false;
		i = 0;
		while (i < RULE_COUNT)
		{
			rule = machine->rules[i];
			first_build_from_rule(machine, rule, &did_add);
			i++;
		}
	}
}
