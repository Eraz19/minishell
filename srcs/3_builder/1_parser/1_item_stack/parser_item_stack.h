#ifndef PARSER_ITEM_STACK_H
# define PARSER_ITEM_STACK_H

# include "parser_item_stack_type.h"

void	parser_item_stack_init(t_parser_item_stack *stack);
void	parser_item_stack_clear(t_parser_item_stack *stack);
void	parser_item_stack_free(t_parser_item_stack *stack);

t_parser_item	*parser_item_stack_top(const t_parser_item_stack *stack);

#endif
