#include "symbols.h"

bool	symbol_is_nullable(t_lr_machine *machine, t_symbol symbol)
{
	return (machine->nullable_symbols[symbol]);
}

bool	symbols_are_nullable(t_lr_machine *machine, t_symbol *symbols, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		if (!symbol_is_nullable(machine, symbols[i]))
			return (false);
		i++;
	}
	return (true);
}

static void	build_nullable_symbol(t_lr_machine *machine, t_symbol symbol, bool *did_add)
{
	size_t	i;
	t_rule	rule;

	i = 0;
	while (i < RULE_COUNT)
	{
		rule = machine->rules[i++];
		if (rule.lhs != symbol)
			continue ;
		if (rule.rhs_len == 0)
		{
			machine->nullable_symbols[symbol] = true;
			*did_add = true;
		}
		if (symbols_are_nullable(machine, rule.rhs, rule.rhs_len))
		{
			machine->nullable_symbols[symbol] = true;
			*did_add = true;
		}
	}
}

void	symbols_build_nullables(t_lr_machine *machine)
{
	t_symbol	symbol;
	bool		did_add;

	ft_memset(machine->nullable_symbols, false, SYM_COUNT);
	did_add = true;
	while (did_add)
	{
		did_add = false;
		symbol = SYM_NON_TERMINAL_MIN;
		while (symbol < SYM_NON_TERMINAL_MAX)
		{
			build_nullable_symbol(machine, symbol, &did_add);
			symbol++;
		}
	}
}
