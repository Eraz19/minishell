#include "input_stack_.h"

t_error	input_stack_pop(t_input_stack *stack)
{
	t_input_stack_item	*last_item;

	if (!vector_remove(stack, stack->len - 1, (void **)&last_item))
		return (error_sys());
	return (input_stack_item_free(&last_item), error(ERR_NO));
}

t_error	input_stack_push(t_input_stack *stack, t_input_stack_item *item)
{
	if (!vector_push(stack, &item))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	input_stack_get_last(t_input_stack *stack, t_input_stack_item **item)
{
	if (stack->len == 0)
		return (error(ERR_EMPTY_STACK));
	*item = ((t_input_stack_item **)stack->data)[stack->len - 1];
	return (error(ERR_NO));
}
