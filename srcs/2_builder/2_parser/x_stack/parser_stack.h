#ifndef PARSER_STACK_H
# define PARSER_STACK_H

# include "builder.h"
# include <stdbool.h>

# define STACK_INITIAL_CAP	16

t_stack_item	*stack_top(t_stack *stack);

#endif
