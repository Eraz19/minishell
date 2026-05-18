#include "shell.h"
# include <stdio.h>
# include "debug.h"

void	var_dump(t_var *var)
{
	if (var->value)
		printf("VAR name='%s' value='%s' exported=%s readonly=%s\n",
			var->name,
			var->value,
			bool_to_string(var->export),
			bool_to_string(var->readonly));
	else
		printf("VAR name='%s' value=NULL exported=%s readonly=%s\n",
			var->name,
			bool_to_string(var->export),
			bool_to_string(var->readonly));
}

void	var_dump_all(void)
{
	t_shell 	*shell;
	t_var_list	*var_list;
	t_var		*var;
	size_t		i;

	printf("\nDUMP VARIABLES\n");
	shell = shell_get();
	if (!shell)
		error_print(NULL, "var_dump_all()", ERR_SHELL_NOT_FOUND);
	var_list = &shell->params.variables;
	i = 0;
	while (i < var_list->len)
	{
		var = &((t_var *)var_list->data)[i];
		var_dump(var);
		i++;
	}
}
