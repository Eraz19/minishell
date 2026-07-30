#include "alias_stack_internal.h"
# include <assert.h>

t_error	alias_stack_push(t_alias_stack *stack, const t_string *name)
{
	t_string	dup;
	t_error		err;

	if (!string_init(&dup, name->len + 1, name->data, (long)name->len))
		return (error_sys());
	if (vector_push(stack, &dup))
		return (err = error_sys(), string_free(&dup), err);
	return (error(ERR_NO));
}

bool	alias_stack_contains(const t_alias_stack *stack, const t_string *name)
{
	const t_string	*current;
	size_t			i;

	i = 0;
	while (i < stack->len)
	{
		current = &((t_string *)stack->data)[i];
		if (string_cmp(current, name))
			return (true);
		i++;
	}
	return (false);
}

void	alias_stack_pop(t_alias_stack *stack)
{
	t_string	name;
	assert(stack->len > 0);
	(void)vector_pop(stack, &name);
	string_free(&name);
}
