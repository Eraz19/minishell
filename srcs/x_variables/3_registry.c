#include "libft.h"
#include "variable_priv.h"
#include <stdlib.h>

t_error	var_set(t_var_list *variables, const char *name, const char *value)
{
	size_t	var_index;
	t_var	*current_var;
	t_var	new_var;

	if (!variables || !name || !value)
		return (ERR_INVALID_POINTER);
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
	if (!new_var.name || !new_var.value)
		return (free(new_var.name), free(new_var.value), ERR_OUT_OF_MEMORY);
	if (!vector_push(variables, &new_var))
		return (free(new_var.name), free(new_var.value), ERR_OUT_OF_MEMORY);
	return (ERR_NO);
}

t_error	var_set_export(t_var_list *variables, const char *name, bool export)
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
		if (!export)
			return (ERR_VAR_NOT_FOUND);
		new_var = var_new(name, "", export, false);
		if (!new_var.name || !new_var.value)
			return (free(new_var.name), free(new_var.value), ERR_OUT_OF_MEMORY);
		if (!vector_push(variables, &new_var))
			return (free(new_var.name), free(new_var.value), ERR_OUT_OF_MEMORY);
		return (ERR_NO);
	}
	current_var = &((t_var *)variables->data)[var_index];
	current_var->export = export;
	return (ERR_NO);
}

t_error	var_set_readonly(t_var_list *variables, const char *name)
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
		new_var = var_new(name, "", false, true);
		if (!new_var.name || !new_var.value)
			return (free(new_var.name), free(new_var.value), ERR_OUT_OF_MEMORY);
		if (!vector_push(variables, &new_var))
			return (free(new_var.name), free(new_var.value), ERR_OUT_OF_MEMORY);
		return (ERR_NO);
	}
	current_var = &((t_var *)variables->data)[var_index];
	current_var->readonly = true;
	return (ERR_NO);
}

t_error	var_get(t_var_list *variables, const char *var_name, t_var **dst_var)
{
	size_t	var_index;

	if (!variables || !var_name || !dst_var)
		return (ERR_INVALID_POINTER);
	if (!var_find(variables, var_name, &var_index))
		return (ERR_VAR_NOT_FOUND);
	*dst_var = &((t_var *)variables->data)[var_index];
	return (ERR_NO);
}

t_error	var_unset(t_var_list *variables, const char *var_name)
{
	size_t	var_index;
	t_var	*var;

	if (!variables || !var_name)
		return (ERR_INVALID_POINTER);
	if (!var_find(variables, var_name, &var_index))
		return (ERR_NO);
	var = &((t_var *)variables->data)[var_index];
	if (var->readonly)
		return (ERR_VAR_READ_ONLY);
	var_free(var);
	if (!vector_remove(variables, var_index, NULL))
		return (ERR_INDEX_OUT_OF_BOUND);
	return (ERR_NO);
}
