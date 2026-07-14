#include "functions.h"

t_error	function_get(t_functions *functions, const char *name, t_function **out)
{
	t_function	*function;

	function = hashmap_get(functions, name);
	if (function == NULL)
		return (error(ERR_VAR_NOT_FOUND));
	function->active_count++;
	*out = function;
	return (error(ERR_NO));
}
