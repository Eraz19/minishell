#include "functions_priv.h"

void	function_unset(t_functions *functions, const char *name)
{
	t_function	*function;

	function = hashmap_get(functions, name);
	if (function == NULL)
		return ;
	hashmap_remove(functions, name);
	function->pending_free = true;
	if (function->active_count == 0)
		function_free(&function);
}
