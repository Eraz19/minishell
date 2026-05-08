#include "libft.h"
#include "variable_priv.h"
#include <stdlib.h>

// value can be NULL.
// errors can be ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY / ERR_LIBC.
t_error	var_set(t_var_list *variables, const char *name, const char *value)
{
	size_t	var_index;
	t_var	*current_var;
	t_var	new_var;

	if (!var_name_is_valid(name))
		return (ERR_VAR_INVALID_NAME);
	if (var_find(variables, name, &var_index))
	{
		current_var = &((t_var *)variables->data)[var_index];
		if (current_var->readonly)
			return (ERR_VAR_READ_ONLY);
		return (var_update_value(current_var, value));
	}
	new_var = var_new(name, value, false, false);
	if (!new_var.name || (value && !new_var.value))
		return (var_free(&new_var), ERR_LIBC);
	if (!vector_push(variables, &new_var))
		return (var_free(&new_var), ERR_LIBC);
	return (ERR_NO);
}

// errors can be ERR_VAR_NOT_FOUND / ERR_LIBC.
t_error	var_get(const t_var_list *variables, const char *name, char **dst_val)
{
	size_t	var_index;
	t_var	*var;
	char	*res;

	if (!var_find(variables, name, &var_index))
		return (ERR_VAR_NOT_FOUND);
	var = &((t_var *)variables->data)[var_index];
	res = str_dup(var->value);
	if (!res)
		return (ERR_LIBC);
	*dst_val = res;
	return (ERR_NO);
}
