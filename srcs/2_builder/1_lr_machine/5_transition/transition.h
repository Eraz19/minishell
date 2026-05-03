#ifndef TRANSITION_H
# define TRANSITION_H

# include "parser.h"

void	transition_init(t_vector *transitions);
bool	transition_build_table(t_lr_machine *machine);
void	transition_free(t_vector *transitions);

#endif
