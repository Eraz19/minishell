#include "variable_priv.h"
#include <stdlib.h>
#include <unistd.h>

t_error	var_export(t_var_list *variables, const char *name)
{
	size_t	var_index;
	t_var	new_var;
	t_var	*current_var;

	if (!variables || !name)
		return (ERR_INVALID_POINTER);
	if (!var_name_is_valid(name))
		return (ERR_VAR_INVALID_NAME);
	if (!var_find(variables, name, &var_index))
	{
		new_var = var_new(name, NULL, true, false);
		if (!new_var.name)
			return (free(new_var.name), ERR_LIBC);
		if (!vector_push(variables, &new_var))
			return (free(new_var.name), ERR_LIBC);
		return (ERR_NO);
	}
	current_var = &((t_var *)variables->data)[var_index];
	current_var->export = true;
	return (ERR_NO);
}

t_error	var_export_print(t_var_list *variables)
{
	size_t	i;
	t_var	*var;
	size_t	len;

	i = 0;
	while (i < variables->len)
	{
		var = &((t_var *)variables->data)[i++];
		if (!var->export)
			continue ;
		len = str_len(var->name);
		write(STDERR_FILENO, var->name, len);
		if (!var->value)
			continue ;
		len = str_len(var->value);
		write(STDERR_FILENO, var->value, len);
	}
}
