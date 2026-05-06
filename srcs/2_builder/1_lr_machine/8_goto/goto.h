#ifndef GOTO_H
# define GOTO_H

# include "builder.h"
# include <limits.h>

# define GOTO_EMPTY	SIZE_T_MAX

void	goto_init(size_t ***gotos);
bool	goto_build_table(t_lr_machine *machine);
bool	go_to(size_t **gotos, size_t current_lr_state_id, t_symbol symbol, size_t *new_lr_state_id);
void	goto_free(size_t lr_states_count, size_t ***gotos);

#endif
