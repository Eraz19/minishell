#include "libft.h"
#include "shell.h"
#include "variables.h"
#include "variables_priv.h"
#include "options.h"
#include "utils.h"
#include <stdlib.h>
# include <assert.h>	// DEBUG

// value can be NULL
// @ret ERR_VAR_READ_ONLY / ERR_LIBC
static inline t_error	var_update_value(
							t_var *var,
							const t_string *value,
							bool export,
							bool readonly)
{
	assert(var != NULL);
	if (var->readonly && value)
		return (error(ERR_VAR_READ_ONLY));
	if (value)
	{
		var->value.len = 0;
		if (!string_append(&var->value, value))
			return (error_sys());
	}
	if (export)
		var->export = true;
	if (readonly)
		var->readonly = true;
	return (error(ERR_NO));
}

static inline t_error	var_create(
							const t_string *name,
							const t_string *value,
							bool export,
							bool readonly)
{
	t_params	*params;
	t_var_list	*list;
	t_var		new_var;
	t_error		err;

	assert(name != NULL);
	params = shell_get_params();
	if (!params)
		return (error(ERR_SHELL_NOT_FOUND));
	list = &params->variables;
	if (!string_init(&new_var.name, 0, name->data, (long)name->len))
		return (error_sys());
	(void)string_init(&new_var.value, 0, NULL, 0);
	if (value && !string_append(&new_var.value, value))
		return (err = error_sys(), var_free_one(&new_var), err);
	new_var.export = export
		|| option_is_active_in(params->options, OPT_EXPORT_ALL);
	new_var.readonly = readonly;
	if (!vector_push(list, &new_var))
		return (err = error_sys(), var_free_one(&new_var), err);
	return (error(ERR_NO));
}

t_error	var_set(
			const t_string *name,
			const t_string *value,
			bool export,
			bool readonly)
{
	t_params	*params;
	t_var_list	*list;
	size_t		var_index;
	t_var		*current_var;

	assert(name != NULL);
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
