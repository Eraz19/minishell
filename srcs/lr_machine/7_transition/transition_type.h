#ifndef TRANSITION_TYPE_H
# define TRANSITION_TYPE_H

# include "symbols_type.h"
# include <stddef.h>

typedef struct s_transition
{
	size_t		from_lr_state_id;
	t_symbol	symbol;
	size_t		to_lr_state_id;
}	t_transition;

#endif
