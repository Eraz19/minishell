#ifndef PARSER_HERE_STACK_H
# define PARSER_HERE_STACK_H

# include "cst_type.h"
# include "parser_here_stack_type.h"

void	parser_here_stack_init(t_parser_here_stack *stack);
void	parser_here_stack_clear(t_parser_here_stack *stack);
void	parser_here_stack_free(t_parser_here_stack *stack);

t_cst_node	*parser_here_stack_first(const t_parser_here_stack *stack);

#endif
