#include "libft.h"
#include "shell.h"
#include "variables_priv.h"
#include "options.h"
#include <stdlib.h>

// value can be NULL
// @ret ERR_VAR_READ_ONLY / ERR_LIBC
static t_error	var_update_value(
	t_var *var,
	const char *value,
	bool export,
	bool readonly)
{
	char	*new_value;

	if (var->readonly && value)
		return (ERR_VAR_READ_ONLY);
	if (value)
	{
		new_value = str_dup(value);
		if (!new_value)
			return (ERR_LIBC);
		free(var->value);
		var->value = new_value;
	}
	if (export)
		var->export = true;
	if (readonly)
		var->readonly = true;
	return (ERR_NO);
}

t_error	var_set(const char *name, const char *value, bool export, bool readonly)
{
	t_shell		*shell;
	t_var_list	*list;
	size_t		var_index;
	t_var		*current_var;
	t_var		new_var;

	if (!var_name_is_valid(name))
		return (ERR_VAR_INVALID_NAME);
	shell = shell_get();
	if (!shell)
		return (ERR_SHELL_NOT_FOUND);
	list = &shell->params.variables;
	if (var_find(list, name, &var_index))
	{
		current_var = &((t_var *)list->data)[var_index];
		return (var_update_value(current_var, value, export, readonly));
	}
	if (option_is_active(OPT_EXPORT_ALL))
		export = true;
	new_var = var_new(name, value, export, readonly);
	if (!new_var.name || (value && !new_var.value))
		return (var_free_one(&new_var), ERR_LIBC);
	if (!vector_push(list, &new_var))
		return (var_free_one(&new_var), ERR_LIBC);
	return (ERR_NO);
}

t_error	var_get(const char *name, char **dst_val)
{
	t_shell		*shell;
	t_var_list	*list;
	size_t		var_index;
	t_var		*var;
	char		*res;

	shell = shell_get();
	if (!shell)
		return (ERR_SHELL_NOT_FOUND);
	list = &shell->params.variables;
	if (!var_name_is_valid(name))
		return (ERR_VAR_INVALID_NAME);
	if (!var_find(list, name, &var_index))
		return (ERR_VAR_NOT_FOUND);
	res = NULL;
	var = &((t_var *)list->data)[var_index];
	if (var->value)
	{
		res = str_dup(var->value);
		if (!res)
			return (ERR_LIBC);
	}
	*dst_val = res;
	return (ERR_NO);
}

t_error	var_unset(const char *name)
{
	t_shell		*shell;
	t_var_list	*list;
	size_t		var_index;
	t_var		*var;

	if (!var_name_is_valid(name))
		return (ERR_VAR_INVALID_NAME);
	shell = shell_get();
	if (!shell)
		return (ERR_SHELL_NOT_FOUND);
	list = &shell->params.variables;
	if (!var_find(list, name, &var_index))
		return (ERR_NO);
	var = &((t_var *)list->data)[var_index];
	if (var->readonly)
		return (ERR_VAR_READ_ONLY);
	var_free_one(var);
	if (!vector_remove(list, var_index, NULL))
		return (ERR_INDEX_OUT_OF_BOUND);
	return (ERR_NO);
}
