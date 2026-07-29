#ifndef GENERATOR_QUALIFIERS_H
# define GENERATOR_QUALIFIERS_H

# include "grammar_qualifiers.h"
# include "grammar_rules.h"
# include "grammar_actions.h"
# include "libft.h"

void	qualifiers_init(t_qualifier **qualifiers);
void	qualifiers_free(t_qualifier **qualifiers);

bool	qualifiers_build_table(
			t_qualifier **qualifiers,
			const t_rule rules[RULE_COUNT],
			const t_vector *lr_states,
			const t_action *actions);

#endif
