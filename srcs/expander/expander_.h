#ifndef EXPANDER__H
# define EXPANDER__H

# include "expander.h"
# include "expander_field_.h"

typedef struct s_expander
{
	t_error				err;
	t_expander_role		role;
	t_expander_word		word;
	t_expander_fields	fields;
	t_expander_word		word_exp;
	t_expander_fields	fields_exp;
}	t_expander;

void	expander_free(t_expander *state);
void	expander_init(t_expander *state, t_expander_role role);
t_error	expander_load(t_expander *state, t_buff word, t_context_stack *stack);

#endif
