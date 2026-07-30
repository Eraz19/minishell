#include "positionals.h"
# include <assert.h>	// DEBUG

void	positionals_init_stack(t_positionals_stack *stack)
{
	assert(stack != NULL);
	(void)vector_init(stack, sizeof(t_positionals), 0);
}

void	positionals_free_item(void *positionals)
{
	assert(positionals != NULL);
	vector_free(positionals, string_free_void);
}

void	positionals_free_stack(t_positionals_stack *stack)
{
	assert(stack != NULL);
	vector_free(stack, positionals_free_item);
}

void	positionals_clear_stack(t_positionals_stack *stack)
{
	vector_clear(stack, positionals_free_item);
}
