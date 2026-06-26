#include "libft.h"
#include "shell.h"
#include "variables.h"
#include "variables_priv.h"
#include "options.h"
#include "utils.h"
#include <stdlib.h>

static inline t_error	var_save_err_and_free(t_var *var)
{
	t_error	err;

	err = error_sys();
	var_free_one(var);
	return (err);
}

// value can be NULL
// @ret ERR_VAR_READ_ONLY / ERR_LIBC
static inline t_error	var_update_value(
	t_var *var,
	const char *value,
	bool export,
	bool readonly)
{
	char	*new_value;

	if (var->readonly && value)
		return (error(ERR_VAR_READ_ONLY));
	if (value)
	{
		new_value = str_dup(value);
		if (!new_value)
			return (error_sys());
		free(var->value);
		var->value = new_value;
	}
	if (export)
		var->export = true;
	if (readonly)
		var->readonly = true;
	return (error(ERR_NO));
}

static inline t_error	var_create(const char *name, const char *value, bool export, bool readonly)
{
	t_params	*params;
	t_var_list	*list;
	bool		export_is_active;
	t_var		new_var;
	t_error		err;

	params = shell_get_params();
	if (!params)
		return (error(ERR_SHELL_NOT_FOUND));
	list = &params->variables;
	err = option_is_active(OPT_EXPORT_ALL, &export_is_active);
	if (err.type)
		return (err);
	if (export_is_active == true)
		export = true;
	new_var = var_new(name, value, export, readonly);
	if (!new_var.name || (value && !new_var.value))
		return (var_save_err_and_free(&new_var));
	if (!vector_push(list, &new_var))
		return (var_save_err_and_free(&new_var));
	return (error(ERR_NO));
}

t_error	var_set(const char *name, const char *value, bool export, bool readonly)
{
	t_params	*params;
	t_var_list	*list;
	size_t		var_index;
	t_var		*current_var;

	if (!name_is_valid(name))
		return (error(ERR_VAR_INVALID_NAME));
	params = shell_get_params();
	if (!params)
		return (error(ERR_SHELL_NOT_FOUND));
	list = &params->variables;
	if (var_find(list, name, &var_index))
	{
		current_var = &((t_var *)list->data)[var_index];
		return (var_update_value(current_var, value, export, readonly));
	}
	return (var_create(name, value, export, readonly));
}
