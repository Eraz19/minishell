#include "parser_item_stack_type.h"
#include "parser_item_stack.h"
#include "cst.h"
# include <assert.h>	// DEBUG

static void	parser_item_free(void *raw_item)
{
	t_parser_item	*item;

	item = raw_item;
	cst_node_free(&item->cst_node);
}

void	parser_item_stack_init(t_parser_item_stack *stack)
{
	(void)vector_init(stack, sizeof(t_parser_item), 0);
}

void	parser_item_stack_clear(t_parser_item_stack *stack)
{
	vector_clear(stack, parser_item_free);
}

void	parser_item_stack_free(t_parser_item_stack *stack)
{
	vector_free(stack, parser_item_free);
}

t_parser_item	*parser_item_stack_top(const t_parser_item_stack *stack)
{
	assert(stack != NULL);
	assert(stack->len > 0);
	if (stack->len == 0)
		return (NULL);
	return (&((t_parser_item *)stack->data)[stack->len - 1]);
}
