#include "libft.h"
#include "shell.h"
#include <stdlib.h>

static t_error	var_update_value(t_var *var, const char *value)
{
	char	*new_value;

	if (!value)
		return (ERR_NO);
	new_value = str_dup(value);
	if (!new_value)
		return (ERR_LIBC);
	free(var->value);
	var->value = new_value;
	return (ERR_NO);
}

t_error	var_set(t_var_list *variables, const char *name, const char *value)
{
	size_t	var_index;
	t_var	*current_var;
	t_var	new_var;
	bool	export;

	if (!var_name_is_valid(name))
		return (ERR_VAR_INVALID_NAME);
	if (var_find(variables, name, &var_index))
	{
		current_var = &((t_var *)variables->data)[var_index];
		if (current_var->readonly)
			return (ERR_VAR_READ_ONLY);
		return (var_update_value(current_var, value));
	}
	export = option_is_active(shell_get()->params.options, OPT_EXPORT_ALL);
	new_var = var_new(name, value, export, false);
	if (!new_var.name || (value && !new_var.value))
		return (var_free(&new_var), ERR_LIBC);
	if (!vector_push(variables, &new_var))
		return (var_free(&new_var), ERR_LIBC);
	return (ERR_NO);
}

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
