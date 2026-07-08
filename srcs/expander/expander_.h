#ifndef EXPANDER__H
# define EXPANDER__H

# include "field_.h"
# include "expander.h"

typedef	struct s_expander_args
{
	t_string				value;
	t_exp_flag				flags;
	const t_context_stack	*contexts;
	ssize_t					assignment_offset;
}	t_expander_args;

typedef struct s_expander
{
	t_string	ifs;
	t_error		err;
	t_exp_flag	flags;
	t_word		word;
	t_fields	fields;
	t_word		word_exp;
	t_fields	fields_exp;
	bool		in_operand;
	ssize_t		assignment_offset;
}	t_expander;

void	expander_free(t_expander *expander);
void	expander_init(t_expander *expander);
t_error	expander_load(t_expander *expander, t_expander_args *args);

t_error	expand_word(t_expander *expander);
bool    flag_is_active(uint bitset, uint flag);
t_error	get_ifs(t_expander *expander, t_string	*ifs);
t_error	forward_word_item(t_word *word_exp, t_word *word);

#endif
