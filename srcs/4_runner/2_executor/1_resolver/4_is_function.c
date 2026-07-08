#include "libft.h"
#include "cmd_resolver_priv.h"
#include "functions.h"

bool	cmd_name_is_function(
			const t_functions *functions,
			const char *name,
			const t_function **out_function)
{
	*out_function = hashmap_get(functions, name);
	return (*out_function != NULL);
}
