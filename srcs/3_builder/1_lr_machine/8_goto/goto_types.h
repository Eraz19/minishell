#ifndef GOTOS_TYPES_H
# define GOTOS_TYPES_H

# include "symbols_type.h"
# include <stddef.h>

typedef struct s_goto
{
	size_t		from_lr_state_id;
	t_symbol	symbol;
	size_t		to_lr_state_id;
}	t_goto;

#endif
