#include "libft.h"
#include "shell.h"
#include "variables.h"
#include "variables_priv.h"
#include "utils.h"
#include <stdlib.h>

t_error	var_get(const char *name, char **dst_val)
{
	t_params	*params;
	t_var_list	*list;
	size_t		var_index;
	t_var		*var;
	char		*res;

	params = shell_get_params();
	if (!params)
		return (error(ERR_SHELL_NOT_FOUND));
	list = &params->variables;
	if (!name_is_valid(name))
		return (error(ERR_VAR_INVALID_NAME));
	if (!var_find(list, name, &var_index))
		return (error(ERR_VAR_NOT_FOUND));
	res = NULL;
	var = &((t_var *)list->data)[var_index];
	if (var->value)
	{
		res = str_dup(var->value);
		if (!res)
			return (error_sys());
	}
	*dst_val = res;
	return (error(ERR_NO));
}
