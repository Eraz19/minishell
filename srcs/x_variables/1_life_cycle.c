#include "variable.h"
#include <stdlib.h>

/* ************************************************************************* */
/*                                  PRIVATE                                  */
/* ************************************************************************* */

t_var	var_new(const char *name, const char *value, bool export, bool ronly)
{
	return ((t_var)
	{
		.name = str_dup(name),
		.value = str_dup(value),
		.export = export,
		.readonly = ronly
	});
}

t_error	var_update_value(t_var *var, const char *value)
{
	char	*new_value;

	new_value = str_dup(value);
	if (!new_value)
		return (ERR_OUT_OF_MEMORY);
	free(var->value);
	var->value = new_value;
	return (ERR_NO);
}

/* ************************************************************************* */
/*                                  PUBLIC                                   */
/* ************************************************************************* */

void	var_free(t_var *var)
{
	if (var->name)
		free(var->name);
	var->name = NULL;
	if (var->value)
		free(var->value);
	var->value = NULL;
}
