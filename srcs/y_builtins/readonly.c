#include "variable.h"
#include <stdlib.h>

// value can be NULL
t_error	readonly(t_var_list *variables, const char *name, const char *value)
{
	size_t	var_index;
	t_var	new_var;
	t_var	*current_var;
	t_error	error;

	if (!var_name_is_valid(name))
		return (ERR_VAR_INVALID_NAME);
	if (!var_find(variables, name, &var_index))
	{
		new_var = var_new(name, value, false, true);
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
	current_var->readonly = true;
	return (ERR_NO);
}

t_error	readonly_print(const t_var_list *variables)
{
	size_t	i;
	t_var	*var;
	t_error	error;

	i = 0;
	while (i < variables->len)
	{
		var = &((t_var *)variables->data)[i++];
		if (!var->readonly)
			continue ;
		error = var_print("readonly ", var);
		if (error != ERR_NO)
			return (error);
	}
	return (ERR_NO);
}
