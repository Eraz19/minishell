#ifndef PARSER_STACK_H
# define PARSER_STACK_H

# include "parser_stack_type.h"

void	parser_stack_init(t_parser_stack *stack);
void	parser_stack_clear(t_parser_stack *stack);
void	parser_stack_free(t_parser_stack *stack);

t_parser_stack_item	*parser_stack_top(const t_parser_stack *stack);

#endif
