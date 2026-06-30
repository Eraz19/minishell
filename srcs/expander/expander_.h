#ifndef EXPANDER__H
# define EXPANDER__H

# include "expander.h"
# include "expander_field_.h"

typedef	struct s_expander_args
{
	t_string				value;
	t_exp_flags		flags;
	const t_context_stack	*contexts;
	ssize_t					assignment_offset;
}	t_expander_args;

typedef struct s_expander
{
	t_error				err;
	t_exp_flags	flags;
	t_expander_word		word;
	t_expander_fields	fields;
	t_expander_word		word_exp;
	t_expander_fields	fields_exp;
	ssize_t				assignment_offset;
}	t_expander;

void	expander_free(t_expander *state);
void	expander_init(t_expander *state);
t_error	expander_load(t_expander *state, t_expander_args *args);

bool    flag_is_active(uint bitset, uint flag);

#endif
