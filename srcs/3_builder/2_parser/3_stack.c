#include "builder.h"

void	parser_stack_init(t_stack *stack)
{
	vector_init(stack, sizeof(t_stack_item), 0);
}

t_stack_item	*parser_stack_top(t_stack *stack)
{
	if (stack->len == 0)
		return (NULL);
	return ((t_stack_item *)stack->data + (stack->len - 1));
}

bool	parser_stack_push(t_stack *stack, t_stack_item *item)
{
	return (vector_push(stack, item));
}

bool	parser_stack_pop(t_stack *stack, t_stack_item *dst)
{
	return (vector_pop(stack, dst));
}

void	parser_stack_free(t_stack *stack)
{
	vector_free(stack, NULL);
}
