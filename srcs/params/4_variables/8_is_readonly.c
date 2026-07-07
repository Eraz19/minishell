#include "variables.h"
#include "variables_priv.h"

bool	var_is_readonly(const t_var_list *variables, const char *name)
{
	size_t		index;
	const t_var	*var;

	if (!var_find_from_const(variables, name, &index))
		return (false);
	var = &((const t_var *)variables->data)[index];
	return (var->readonly);
}
