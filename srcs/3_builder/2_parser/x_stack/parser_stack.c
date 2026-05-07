#include "parser_stack.h"

t_stack_item	*stack_top(t_stack *stack)
{
	if (stack->len == 0)
		return (NULL);
	return ((t_stack_item *)stack->data + (stack->len - 1));
}

bool	stack_init(t_stack *stack)
{
	return (vector_init(stack, sizeof(t_stack_item), STACK_INITIAL_CAP));
}

bool	stack_push(t_stack *stack, t_stack_item item)
{
	return (vector_push(stack, &item));
}

bool	stack_pop(t_stack *stack, t_stack_item *dst)
{
	return (vector_pop(stack, dst));
}

void	stack_free(t_stack *stack)
{
	vector_free(stack);
}
