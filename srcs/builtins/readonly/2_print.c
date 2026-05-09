#include "shell.h"
#include <stdlib.h>

t_error	readonly_print(const t_shell *shell, const char *builtin)
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
		if (!var->readonly)
			continue ;
		error = var_print("readonly ", var);
		if (error != ERR_NO)
			return (error_print(builtin, NULL, error));
	}
	return (ERR_NO);
}
