#include "variable.h"
#include <stdlib.h>

// value can be NULL
static t_error	export_add_one(
	t_var_list *variables,
	const char *name,
	const char *value)
{
	size_t	var_index;
	t_var	new_var;
	t_var	*current_var;
	t_error	error;

	if (!var_name_is_valid(name))
		return (ERR_VAR_INVALID_NAME);
	if (!var_find(variables, name, &var_index))
	{
		new_var = var_new(name, value, true, false);
		if (!new_var.name || (value && !new_var.value))
			return (var_free(&new_var), ERR_LIBC);
		if (!vector_push(variables, &new_var))
			return (var_free(&new_var), ERR_LIBC);
		return (ERR_NO);
	}
	if (value)
	{
		error = var_set(variables, name, value);
		if (error != ERR_NO)
			return (error);
	}
	current_var = &((t_var *)variables->data)[var_index];
	current_var->export = true;
	return (ERR_NO);
}

t_error	export_add(t_var_list *variables, const char *string)
{
	char	*name;
	char	*value;
	t_error	error;

	if (str_chr(string, '=') == NULL)
		return (export_add_one(variables, name, NULL));
	error = var_split(string, &name, &value);
	if (error != ERR_NO)
		return (error);
	error = export_add_one(variables, name, value);
	free(name);
	free(value);
	return (error);
}
