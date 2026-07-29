#ifndef GENERATOR_FIRST_H
# define GENERATOR_FIRST_H

# include "grammar_rules.h"
# include <stdbool.h>

typedef struct s_first_param
{
	const t_symbol	*symbols;
	size_t			count;
	t_symbol		lookahead;
	bool			has_lookahead;
	bool			result[SYM_TERMINAL_MAX + 1];
}	t_first_param;

void	first(
			const bool first[SYM_COUNT][SYM_TERMINAL_MAX + 1],
			const bool nullable_symbols[SYM_COUNT],
			t_first_param *param);
void	first_build_table(
			const t_rule rules[RULE_COUNT],
			const bool nullable_symbols[SYM_COUNT],
			bool first[SYM_COUNT][SYM_TERMINAL_MAX + 1]);

#endif
