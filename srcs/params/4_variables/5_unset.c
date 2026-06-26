#include "libft.h"
#include "shell.h"
#include "variables.h"
#include "variables_priv.h"
#include "utils.h"
#include <stdlib.h>

t_error	var_unset(const char *name)
{
	t_params	*params;
	t_var_list	*list;
	size_t		var_index;
	t_var		*var;

	if (!name_is_valid(name))
		return (error(ERR_VAR_INVALID_NAME));
	params = shell_get_params();
	if (!params)
		return (error(ERR_SHELL_NOT_FOUND));
	list = &params->variables;
	if (!var_find(list, name, &var_index))
		return (error(ERR_NO));
	var = &((t_var *)list->data)[var_index];
	if (var->readonly)
		return (error(ERR_VAR_READ_ONLY));
	var_free_one(var);
	if (!vector_remove(list, var_index, NULL))
		return (error(ERR_INDEX_OUT_OF_BOUND));
	return (error(ERR_NO));
}
