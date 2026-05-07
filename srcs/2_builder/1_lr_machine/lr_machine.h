#ifndef LR_MACHINE_H
# define LR_MACHINE_H

# include "parser.h"

void	lr_machine_init(t_lr_machine *machine);
bool	lr_machine_build(t_lr_machine *machine);
void	lr_machine_free(t_lr_machine *machine);

#endif
