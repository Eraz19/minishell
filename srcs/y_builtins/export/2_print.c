#include "builtin_error.h"
#include <stdlib.h>

t_error	export_print(const t_shell *shell, const char *builtin)
{
	size_t				i;
	const t_var_list	*variables;
	t_var				*var;
	t_error				error;

	variables = &shell->variables;
	i = 0;
	while (i < variables->len)
	{
		var = &((t_var *)variables->data)[i++];
		if (!var->export)
			continue ;
		error = var_print("export ", var);
		if (error != ERR_NO)
			return (builtin_print_custom(shell, builtin, NULL, error));
	}
	return (ERR_NO);
}
