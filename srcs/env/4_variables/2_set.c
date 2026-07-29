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
	bool	export_all_is_active;
	t_error	err;

	assert(var != NULL);
	if (var->readonly && value)
		return (error(ERR_VAR_READ_ONLY));
	err = option_is_active(OPT_EXPORT_ALL, &export_all_is_active);
	if (err.type)
		return (err);
	if (value && value->data)
	{
		var->value.len = 0;
		if (!string_append(&var->value, value))
			return (error_sys());
	}
	if (export || export_all_is_active)
		var->export = true;
	if (readonly)
		var->readonly = true;
	return (error(ERR_NO));
}

// @ret ERR_LIBC
static inline t_error	var_create(
							const t_string *name,
							const t_string *value,
							bool export,
							bool readonly)
{
	t_params	*params;
	t_var_list	*list;
	t_var		*new_var;
	t_error		err;

	assert(name != NULL);
	params = shell_get_params();
	assert(params != NULL);
	list = &params->variables;
	new_var = malloc(sizeof(*new_var));
	if (new_var == NULL)
		return (error_sys());
	(void)string_init(&new_var->value, 0, NULL, 0);
	if (value && !string_append(&new_var->value, value))
		return (err = error_sys(), var_free_one(new_var), err);
	new_var->export = export
		|| option_is_active_in(params->options, OPT_EXPORT_ALL);
	new_var->readonly = readonly;
	if (!hashmap_put(list, name->data, new_var))
		return (err = error_sys(), var_free_one(new_var), err);
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
	t_var		*current_var;
	t_error		err;

	assert(name != NULL);
	if (!name_is_valid_str(name))
		return (error(ERR_VAR_INVALID_NAME));
	params = shell_get_params();
	assert(params != NULL);
	list = &params->variables;
	current_var = hashmap_get(list, name->data);
	if (current_var != NULL)
		err = var_update_value(current_var, value, export, readonly);
	else
		err = var_create(name, value, export, readonly);
	if (err.type == ERR_NO && str_cmp(name->data, "PATH") == 0)
		cmd_cache_clear(&params->cmd_cache);
	return (err);
}
