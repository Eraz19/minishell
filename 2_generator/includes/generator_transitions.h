#ifndef GENERATOR_TRANSITIONS_H
# define GENERATOR_TRANSITIONS_H

# include "libft.h"
# include "grammar_symbols.h"
# include "generator.h"

typedef struct s_transition
{
	size_t		from_lr_state_id;
	t_symbol	symbol;
	size_t		to_lr_state_id;
}	t_transition;

void	transition_init(t_vector *transitions);
void	transition_free(t_vector *transitions);

bool	transition_build_table(t_lr_generator *generator);

#endif
