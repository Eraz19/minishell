#include "variable.h"
#include <stdlib.h>

t_error	export_print(const t_var_list *variables)
{
	size_t	i;
	t_var	*var;
	t_error	error;

	i = 0;
	while (i < variables->len)
	{
		var = &((t_var *)variables->data)[i++];
		if (!var->export)
			continue ;
		error = var_print("export ", var);
		if (error != ERR_NO)
			return (error);
	}
	return (ERR_NO);
}
