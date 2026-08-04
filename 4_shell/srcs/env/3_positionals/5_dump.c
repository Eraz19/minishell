#include "shell.h"
#include <stdio.h>	// DEBUG

static inline void	positionals_dump_depth(t_positionals_stack *stack, size_t depth)
{
	t_positionals	*positionals;
	size_t			count;
	size_t			i;
	t_string		*param;

	positionals = &((t_positionals *)stack->data)[depth];
	count = positionals->len;
	i = 0;
	while (i < count)
	{
		param = &((t_string *)positionals->data)[i];
		fprintf(stderr, "POSITIONALS[%zu] %zu='%s'\n", depth, i, param->data);
		i++;
	}
	fprintf(stderr, "POSITIONALS #=%zu\n", count);
}

void	positionals_dump(void)
{
	t_shell 			*shell;
	t_positionals_stack	*stack;
	size_t				count;
	size_t				i;

	fprintf(stderr, "\nDUMP POSITIONALS\n");
	shell = shell_get();
	if (!shell)
		error_print(error(ERR_SHELL_NOT_FOUND), "positionals_dump()", NULL, NULL);
	stack = &shell->params.positionals_stack;
	count = stack->len;
	i = 0;
	while (i < count)
	{
		positionals_dump_depth(stack, i);
		i++;
		if (i < count)
			fprintf(stderr, "---\n");
	}
}
