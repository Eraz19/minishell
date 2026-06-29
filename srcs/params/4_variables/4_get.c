#include "libft.h"
#include "shell.h"
#include "variables.h"
#include "variables_priv.h"
#include "utils.h"
#include <stdlib.h>
# include <assert.h>	// DEBUG

t_error	var_get(const t_string *name, t_string *dst_val)
{
	t_params	*params;
	t_var_list	*list;
	size_t		var_index;
	t_var		*var;

	assert(name != NULL);
	assert(dst_val != NULL);
	params = shell_get_params();
	if (!params)
		return (error(ERR_SHELL_NOT_FOUND));
	list = &params->variables;
	if (!name_is_valid(name))
		return (error(ERR_VAR_INVALID_NAME));
	if (!var_find(list, name, &var_index))
		return (error(ERR_VAR_NOT_FOUND));
	var = &((t_var *)list->data)[var_index];
	if (var->value.data)
	{
		if (!string_dup(dst_val, &var->value))
			return (error_sys());
	}
	return (error(ERR_NO));
}

t_error	var_get_from_const(const char *name, t_string *dst_val)
{
	t_params	*params;
	t_var_list	*list;
	size_t		var_index;
	t_var		*var;

	assert(name != NULL);
	assert(dst_val != NULL);
	params = shell_get_params();
	if (!params)
		return (error(ERR_SHELL_NOT_FOUND));
	list = &params->variables;
	if (!name_is_valid_from_const(name))
		return (error(ERR_VAR_INVALID_NAME));
	if (!var_find_from_const(list, name, &var_index))
		return (error(ERR_VAR_NOT_FOUND));
	var = &((t_var *)list->data)[var_index];
	if (var->value.data)
	{
		if (!string_dup(dst_val, &var->value))
			return (error_sys());
	}
	return (error(ERR_NO));
}
