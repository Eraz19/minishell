#include "utils.h"
<<<<<<< HEAD:srcs/alias/stack/_init.c
#include "_OLD_alias.h"
#include "alias_stack_.h"
=======
#include "alias_stack.h"
>>>>>>> 91e05ce91f47e2f34fa82d902ba7abd90f4c66eb:srcs/TO_ENV/DO_TO_ENV/stack/init.c

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
