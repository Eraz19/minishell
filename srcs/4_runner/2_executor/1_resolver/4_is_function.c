#include "cmd_resolver_priv.h"
#include "params.h"

bool	cmd_name_is_function(const char *name, t_function **out_function)
{
	t_error	err;

	err = params_get_function(name, out_function);
	return (err.type == ERR_NO);
}
