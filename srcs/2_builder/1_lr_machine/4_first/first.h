#ifndef FIRST_H
# define FIRST_H

# include "builder.h"

typedef struct s_first_param
{
	t_symbol	*symbols;
	size_t		count;
	t_symbol	lookahead;
	bool		has_lookahead;
	bool		result[SYM_TERMINAL_MAX + 1];
}	t_first_param;

void	first_build_table(t_lr_machine *machine);
void	first(t_lr_machine *machine, t_first_param *param);

#endif
