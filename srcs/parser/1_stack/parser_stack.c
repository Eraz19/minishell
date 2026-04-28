#include "parser_stack.h"
#include "libft.h"
#include <limits.h>
#include <stdlib.h>

bool	stack_init(t_stack *stack)
{
	stack->items = malloc(STACK_INITIAL_CAP * sizeof(*stack->items));
	if (!stack->items)
		return (false);
	stack->cap = STACK_INITIAL_CAP;
	stack->len = 0;
	return (true);
}

bool	stack_grow(t_stack *stack)
{
	size_t			new_cap;
	t_stack_item	*new_items;

	if (stack->cap > SIZE_T_MAX / 2)
		return (false);
	new_cap = stack->cap * 2;
	if (new_cap == 0)
		new_cap = STACK_INITIAL_CAP;
	new_items = malloc(new_cap * sizeof(*new_items));
	if (!new_items)
		return (false);
	ft_memcpy(new_items, stack->items, stack->len * sizeof(*new_items));
	free(stack->items);
	stack->items = new_items;
	stack->cap = new_cap;
	return (true);
}

bool	stack_push(t_stack *stack, t_stack_item item)
{
	if (stack->cap == stack->len)
		if (!stack_grow(stack))
			return (false);
	stack->items[stack->len] = item;
	stack->len++;
	return (true);
}

bool	stack_pop(t_stack *stack, t_stack_item *dst)
{
	if (stack->len == 0)
		return (false);
	stack->len--;
	*dst = stack->items[stack->len];
	return (true);
}

void	stack_free(t_stack *stack)
{
	free(stack->items);
	stack->items = NULL;
	stack->cap = 0;
	stack->len = 0;
}
