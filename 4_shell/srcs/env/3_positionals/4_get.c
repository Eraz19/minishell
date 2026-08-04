#include "positionals.h"
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

t_error	positionals_get(
	const t_positionals_stack *stack,
	const t_positionals **dst)
{
	assert(stack != NULL);
	assert(dst != NULL);
	if (stack->len == 0)
		return (error(ERR_VAR_NOT_FOUND));
	*dst = &((t_positionals *)stack->data)[stack->len - 1];
	return (error(ERR_NO));
}

static inline bool	positionals_name_is_digits_only(
						const char *name,
						size_t name_len)
{
	size_t	i;

	assert(name != NULL);
	assert(name[0] != '\0');
	assert(name_len > 0);
	i = 0;
	while (name[i])
	{
		if (name[i] < '0' || name[i] > '9')
			return (false);
		i++;
	}
	return (i != 0);
}

static inline t_error	positionals_get_one_priv(
							const t_positionals_stack *stack,
							const char *name,
							size_t name_len,
							t_string *dst)
{
	t_positionals	*positionals;
	size_t			index;
	t_string		*string;

	assert(stack != NULL);
	assert(stack->len > 0);
	assert(name != NULL);
	assert(name_len > 0);
	assert(dst != NULL);
	positionals = &((t_positionals *)stack->data)[stack->len - 1];
	if (name[0] == '#' && name[1] == '\0')
	{
		if (!string_append_format(dst, "%i", (int)positionals->len))
			return (error_sys());
		return (error(ERR_NO));
	}
	if (!positionals_name_is_digits_only(name, name_len))
		return (error(ERR_VAR_INVALID_NAME));
	index = ft_atozu(name);
	if (index == SIZE_MAX)
		return (error_sys());
	if (index == 0 || index > positionals->len)
		return (error(ERR_VAR_NOT_FOUND));
	string = &((t_string *)positionals->data)[index - 1];
	if (!string_dup(dst, string))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	positionals_get_one(
			const t_positionals_stack *stack,
			const t_string *name,
			t_string *dst)
{
	return (positionals_get_one_priv(stack, name->data, name->len, dst));
}

t_error	positionals_get_one_cst(
			const t_positionals_stack *stack,
			const char *name,
			t_string *dst)
{
	return (positionals_get_one_priv(stack, name, str_len(name), dst));
}
