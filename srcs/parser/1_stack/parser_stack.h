#ifndef PARSER_STACK_H
# define PARSER_STACK_H

# include "parser.h"
# include <stdbool.h>

# define STACK_INITIAL_CAP	16

bool	stack_init(t_stack *stack);
bool	stack_grow(t_stack *stack);
bool	stack_push(t_stack *stack, t_stack_item item);
bool	stack_pop(t_stack *stack, t_stack_item *dst);
void	stack_free(t_stack *stack);

#endif
