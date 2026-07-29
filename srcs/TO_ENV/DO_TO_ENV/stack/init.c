#include "utils.h"
#include "alias_stack.h"

void	alias_stack_init(t_alias_stack *stack)
{
	vector_init(stack, sizeof(char *), 0);
}

void	alias_stack_clear(t_alias_stack *stack)
{
	vector_clear(stack, free_char_ptr_void);
}

void	alias_stack_free(t_alias_stack *stack)
{
	vector_free(stack, free_char_ptr_void);
}
