#include "variables.h"
#include "variables_priv.h"

bool	var_is_readonly(const t_var_list *variables, const char *name)
{
	const t_var	*var;

	var = hashmap_get_const(variables, name);
	return (var != NULL && var->readonly);
}
