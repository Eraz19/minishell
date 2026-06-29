#include "parser_stack_type.h"
# include <assert.h>	// DEBUG

t_parser_stack_item	*parser_stack_top(const t_parser_stack *stack)
{
	assert(stack != NULL);
	assert(stack->len > 0);
	if (stack->len == 0)
		return (NULL);
	return (&((t_parser_stack_item *)stack->data)[stack->len - 1]);
}
