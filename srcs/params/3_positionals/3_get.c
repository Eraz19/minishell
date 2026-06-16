#include "positionals.h"
#include <stdint.h>

t_error	positionals_get(const t_positionals_stack *stack, t_positionals *dst)
{
	if (stack->len == 0)
		return (error(ERR_VAR_NOT_FOUND));
	*dst = ((t_positionals *)stack->data)[stack->len - 1];
	return (error(ERR_NO));
}

static bool	positionals_name_is_digits_only(const char *name)
{
	size_t	i;

	i = 0;
	while (name[i])
	{
		if (name[i] < '0' || name[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

t_error	positionals_get_one(
	const t_positionals_stack *stack,
	const char *name,
	char **dst)
{
	t_error			err;
	t_positionals	current;
	size_t			index;

	*dst = NULL;
	err = positionals_get(stack, &current);
	if (err.type != ERR_NO)
		return (err);
	if (name[0] == '#' && name[1] == '\0')
	{
		*dst = ft_zutoa(current.count);
		if (!*dst)
			return (error_sys());
		return (error(ERR_NO));
	}
	if (!positionals_name_is_digits_only(name))
		return (error(ERR_VAR_INVALID_NAME));
	index = ft_atozu(name);
	if (index == 0 || index > current.count || index == SIZE_MAX)
		return (error(ERR_VAR_NOT_FOUND));
	*dst = str_dup(current.params[index - 1]);
	if (!*dst)
		return (error_sys());
	return (error(ERR_NO));
}
