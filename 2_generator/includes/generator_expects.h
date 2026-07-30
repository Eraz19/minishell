#ifndef GENERATOR_EXPECTS_H
# define GENERATOR_EXPECTS_H

# include "grammar_rules.h"
# include "libft.h"
# include <stdbool.h>

void	expects_init(bool **expects);
void	expects_free(bool **expects);

bool	expects_build_table(
			bool **expects_table,
			const t_rule rules[RULE_COUNT],
			const t_vector *lr_states);

#endif
