#include "positionals.h"
#include "positionals_priv.h"
#include <stdlib.h>

t_error	positionals_push(
	t_positionals_stack *stack,
	t_positionals *positionals)
{
	if (!vector_push(stack, positionals))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	positionals_pop(t_positionals_stack *stack)
{
	if (stack->len <= 1)
		return (error(ERR_NO));
	if (!vector_pop(stack, positionals_free_item))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	positionals_replace(
	t_positionals_stack *stack,
	t_positionals *positionals)
{
	if (stack->len == 0)
		return (error(ERR_VAR_NOT_FOUND));
	if (!vector_pop(stack, positionals_free_item))
		return (error_sys());
	if (!vector_push(stack, positionals))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	positionals_shift(t_positionals_stack *stack, size_t n)
{
	t_positionals	*positionals;
	size_t			i;

	if (n == 0)
		return (error(ERR_NO));
	if (stack->len == 0)
		return (error(ERR_VAR_NOT_FOUND));
	positionals = &((t_positionals *)stack->data)[stack->len - 1];
	if (n > positionals->count)
		return (error(ERR_SHIFT_INVALID_VALUE));
	i = 0;
	while (i < n)
		free(positionals->params[i++]);
	i = 0;
	while (i + n < positionals->count)
	{
		positionals->params[i] = positionals->params[i + n];
		i++;
	}
	while (i < positionals->count)
		positionals->params[i++] = NULL;
	positionals->count -= n;
	return (error(ERR_NO));
}
