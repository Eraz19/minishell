#include "positionals.h"
#include <stdlib.h>

t_error	positionals_push(t_positionals_stack *stack, t_positionals *positionals)
{
	if (!vector_push(stack, positionals))
		return (ERR_LIBC);
	return (ERR_NO);
}

t_error	positionals_pop(t_positionals_stack *stack)
{
	if (!vector_pop(stack, NULL))
		return (ERR_LIBC);
	return (ERR_NO);
}

t_error	positionals_replace(
	t_positionals_stack *stack,
	t_positionals *positionals)
{
	if (!vector_pop(stack, NULL))
		return (ERR_LIBC);
	if (!vector_push(stack, positionals))
		return (ERR_LIBC);
	return (ERR_NO);
}
