#include "positionals.h"
#include <stdlib.h>
# include <stdio.h>	// TODO: tmp debug

void	positionals_init(t_positionals_stack *stack)
{
	vector_init(stack, sizeof(t_positionals), 0);
}

t_error	positionals_load(t_positionals_stack *stack, int argc, char **argv, size_t start_index)
{
	t_positionals	positionals;

	printf("-------------------------------------\n");
	printf("===> [positionals_load]\n");
	positionals.params = NULL;
	positionals.count = 0;
	if (start_index < (size_t)argc)
	{
		positionals.params = malloc((size_t)argc - start_index);
		if (!positionals.params)
			return (ERR_LIBC);
	}
	while (start_index < (size_t)argc)
	{
		positionals.params[positionals.count] = str_dup(argv[start_index]);
		if (!positionals.params[positionals.count])
			return (ERR_LIBC);
		positionals.count++;
		start_index++;
		printf("-> $%zu = '%s'\n", positionals.count, argv[start_index]);
	}
	if (!vector_push(stack, &positionals))
		return (ERR_LIBC);
	printf("===> [positionals_load]\n");
	printf("-------------------------------------\n\n");
	return (ERR_NO);
}

static void	positionals_free_item(void *positionals)
{
	size_t			i;
	t_positionals	*casted;

	casted = (t_positionals *)positionals;
	i = 0;
	while (i < casted->count)
	{
		free(casted->params[i]);
		i++;
	}
	casted->params = NULL;
	casted->count = 0;
}

void	positionals_free(t_positionals_stack *stack)
{
	vector_free(stack, positionals_free_item);
}
