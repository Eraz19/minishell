#include <stdlib.h>
#include "context.h"

void	context_stack_init(t_context_stack *stack)
{
	*stack = (t_context_stack){0};
	vector_init(stack, sizeof(t_context_stack_item *), 0);
}

static void	free_stack_item(void *item)
{
	free(*(t_context_stack_item **)item);
}

void	context_stack_free(t_context_stack *stack)
{
	vector_free(stack, free_stack_item);
	*stack = (t_context_stack){0};
}

t_error	context_stack_item_init(
			t_context_stack_item **item,
			t_context context)
{
	*item = malloc(sizeof(t_context_stack_item));
	if (*item == NULL)
		return (error_sys());
	**item = (t_context_stack_item){0};
	(*item)->context = context;
	return (error(ERR_NO));
}
