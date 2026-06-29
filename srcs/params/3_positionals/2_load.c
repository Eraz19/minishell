#include "positionals.h"
#include <stdlib.h>
# include "logs.h"	// DEBUG
# include <assert.h>	// DEBUG

static inline t_error	positionals_load_string(
							t_positionals *positionals,
							const char *arg)
{
	t_string	string;
	t_error		err;

	assert(positionals != NULL);
	assert(arg != NULL);
	if (!string_init(&string, 0, arg, -1))
		return (error_sys());
	if (!vector_push(positionals, &string))
	{
		err = error_sys();
		string_free(&string);
		return (err);
	}
	print_pass("$%zu = '%s'\n", positionals->len, string.data);
	return (error(ERR_NO));
}

t_error	positionals_load_stack(
			t_positionals_stack *stack,
			int argc,
			char **argv,
			size_t start_i)
{
	t_positionals	positionals;
	t_error			err;

	assert(stack != NULL);
	assert(argv != NULL);
	assert((size_t)argc >= start_i);
	print_title("positionals_load()");
	if (!vector_init(&positionals, sizeof(t_string), (size_t)argc - start_i))
		return (error_sys());
	while (start_i < (size_t)argc)
	{
		err = positionals_load_string(&positionals, argv[start_i]);
		if (err.type)
			return (vector_free(&positionals, string_free_void), err);
		start_i++;
	}
	if (!vector_push(stack, &positionals))
	{
		err = error_sys();
		vector_free(&positionals, string_free_void);
		return (err);
	}
	print_pass("$# = %zu\n", positionals.len);
	print_result("positionals_load()");
	return (error(ERR_NO));
}
