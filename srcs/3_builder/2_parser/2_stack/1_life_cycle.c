#include "parser_stack_type.h"
#include "parser_stack.h"
#include "cst.h"

void	parser_stack_item_free(void *raw_item)
{
	t_parser_stack_item	*item;

	item = raw_item;
	cst_node_free(&item->cst_node);
}

void	parser_stack_init(t_parser_stack *stack)
{
	(void)vector_init(stack, sizeof(t_parser_stack_item), 0);
}

void	parser_stack_clear(t_parser_stack *stack)
{
	size_t				i;
	t_parser_stack_item	*item;

	i = 0;
	while (i < stack->len)
	{
		item = &((t_parser_stack_item *)stack->data)[i];
		parser_stack_item_free(item);
		i++;
	}
	stack->len = 0;
}

void	parser_stack_free(t_parser_stack *stack)
{
	vector_free(stack, parser_stack_item_free);
}
