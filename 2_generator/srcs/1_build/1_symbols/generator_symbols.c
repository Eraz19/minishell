/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator_symbols.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:40:05 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/04 16:40:06 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator_symbols.h"

static inline bool	symbols_are_nullable(
						bool nullable_symbols[SYM_COUNT],
						const t_symbol *symbols,
						size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		if (nullable_symbols[symbols[i]] == false)
			return (false);
		i++;
	}
	return (true);
}

static inline void	build_nullable_symbol(
						const t_rule rules[RULE_COUNT],
						bool nullable_symbols[SYM_COUNT],
						t_symbol symbol,
						bool *did_add)
{
	size_t			i;
	const t_rule	*rule;

	if (nullable_symbols[symbol] == true)
		return ;
	i = 0;
	while (i < RULE_COUNT)
	{
		rule = &rules[i++];
		if (rule->lhs != symbol)
			continue ;
		if (symbols_are_nullable(nullable_symbols, rule->rhs, rule->rhs_len))
		{
			nullable_symbols[symbol] = true;
			*did_add = true;
		}
	}
}

void	symbols_build_nullables_table(
			const t_rule rules[RULE_COUNT],
			bool nullable_symbols[SYM_COUNT])
{
	t_symbol	symbol;
	bool		did_add;

	symbol = 0;
	while (symbol < SYM_COUNT)
		nullable_symbols[symbol++] = false;
	did_add = true;
	while (did_add)
	{
		did_add = false;
		symbol = SYM_NON_TERMINAL_MIN;
		while (symbol <= SYM_NON_TERMINAL_MAX)
		{
			build_nullable_symbol(rules, nullable_symbols, symbol, &did_add);
			symbol++;
		}
	}
}
