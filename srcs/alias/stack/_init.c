#include <stdlib.h>
#include "alias.h"

void	alias_stack_init(t_alias_stack *stack)
{
	vector_init(stack, sizeof(char *), 0);
}

void	alias_stack_free(t_alias_stack *stack)
{
	vector_free(stack, free);
}
