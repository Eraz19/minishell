#include "generator_first.h"
#include "generator_first_priv.h"
#include "grammar_symbols.h"
#include <stddef.h>

static inline void	first_set_default_and_terminals(
						bool first[SYM_COUNT][SYM_TERMINAL_MAX + 1])
{
	t_symbol	symbol;
	t_symbol	terminal;

	symbol = 0;
	while (symbol < SYM_COUNT)
	{
		terminal = 0;
		while (terminal <= SYM_TERMINAL_MAX)
		{
			first[symbol][terminal] = false;
			terminal++;
		}
		if (symbol <= SYM_TERMINAL_MAX)
			first[symbol][symbol] = true;
		symbol++;
	}
}

static inline void	first_build_from_rule(
						bool first[SYM_COUNT][SYM_TERMINAL_MAX + 1],
						const bool nullable_symbols[SYM_COUNT],
						const t_rule *rule,
						bool *did_add)
{
	size_t		pos;
	t_symbol	symbol;

	pos = 0;
	while (pos < rule->rhs_len)
	{
		symbol = rule->rhs[pos++];
		if (symbol <= SYM_TERMINAL_MAX)
		{
			first_add(&first[rule->lhs][symbol], did_add);
			return ;
		}
		first_add_list(first[rule->lhs], first[symbol], did_add);
		if (nullable_symbols[symbol] == false)
			return ;
	}
}

void	first_build_table(
			const t_rule rules[RULE_COUNT],
			const bool nullable_symbols[SYM_COUNT],
			bool first[SYM_COUNT][SYM_TERMINAL_MAX + 1])
{
	size_t		i;
	bool		did_add;

	first_set_default_and_terminals(first);
	did_add = true;
	while (did_add)
	{
		did_add = false;
		i = 0;
		while (i < RULE_COUNT)
		{
			first_build_from_rule(first, nullable_symbols, &rules[i], &did_add);
			i++;
		}
	}
}
