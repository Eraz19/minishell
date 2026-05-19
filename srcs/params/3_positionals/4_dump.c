#include "shell.h"
# include <stdio.h>

static void	positionals_dump_depth(t_positionals_stack *stack, size_t depth)
{
	t_positionals	*positionals;
	size_t			count;
	size_t			i;

	positionals = &((t_positionals *)stack->data)[depth];
	count = positionals->count;
	i = 0;
	while (i < count)
	{
		printf("POSITIONALS[%zu] %zu='%s'\n", depth, i, positionals->params[i]);
		i++;
	}
	printf("POSITIONALS #=%zu\n", count);
}

void	positionals_dump_all(void)
{
	t_shell 			*shell;
	t_positionals_stack	*stack;
	size_t				count;
	size_t				i;

	printf("\nDUMP POSITIONALS\n");
	shell = shell_get();
	if (!shell)
		error_print(NULL, "positionals_dump_all()", ERR_SHELL_NOT_FOUND);
	stack = &shell->params.positionals;
	count = stack->len;
	i = 0;
	while (i < count)
	{
		positionals_dump_depth(stack, i);
		i++;
		if (i < count)
			printf("---\n");
	}
}
