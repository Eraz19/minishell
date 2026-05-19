#include "positionals.h"
#include <stdlib.h>
# include "logs.h"	// TODO: tmp debug

void	positionals_init(t_positionals_stack *stack)
{
	vector_init(stack, sizeof(t_positionals), 0);
}

static void	positionals_free_partial(t_positionals *positionals)
{
	size_t	i;

	i = 0;
	while (i < positionals->count)
		free(positionals->params[i++]);
	free(positionals->params);
	positionals->params = NULL;
}

t_error	positionals_load(
	t_positionals_stack *stack,
	int argc,
	char **argv,
	size_t start_index)
{
	t_positionals	positionals;

	print_title("positionals_load()");
	positionals.params = NULL;
	positionals.count = 0;
	if (start_index < (size_t)argc)
	{
		positionals.params =
			malloc(sizeof(*positionals.params) * ((size_t)argc - start_index));
		if (!positionals.params)
			return (ERR_LIBC);
	}
	while (start_index < (size_t)argc)
	{
		positionals.params[positionals.count] = str_dup(argv[start_index]);
		if (!positionals.params[positionals.count])
			return (positionals_free_partial(&positionals), ERR_LIBC);
		positionals.count++;
		print_pass("$%zu = '%s'\n", positionals.count, argv[start_index]);
		start_index++;
	}
	if (!vector_push(stack, &positionals))
		return (positionals_free_partial(&positionals), ERR_LIBC);
	print_pass("$# = %zu\n", positionals.count);
	print_result("positionals_load()");
	return (ERR_NO);
}

void	positionals_free_item(void *positionals)
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
	free(casted->params);
	casted->params = NULL;
	casted->count = 0;
}

void	positionals_free(t_positionals_stack *stack)
{
	vector_free(stack, positionals_free_item);
}
