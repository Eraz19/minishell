#include "cmd_resolver_priv.h"
#include "functions.h"

bool	cmd_name_is_function(
			const t_functions *functions,
			const char *name,
			t_function **out_function)
{
	t_error	err;

	err = function_get(functions, name, out_function);
	return (err.type == ERR_NO);
}
