#include "shell.h"
#include "variables_priv.h"
# include <stdio.h>
# include "debug.h"
# include <assert.h>	// DEBUG

void	var_dump_one(const t_var *var)
{
	assert(var != NULL);
	if (var->value.data)
		fprintf(stderr, "VAR name='%s' value='%s' exported=%s readonly=%s\n",
			var->name.data,
			var->value.data,
			bool_to_string(var->export),
			bool_to_string(var->readonly));
	else
		fprintf(stderr, "VAR name='%s' value=NULL exported=%s readonly=%s\n",
			var->name.data,
			bool_to_string(var->export),
			bool_to_string(var->readonly));
}

void	var_dump(void)
{
	t_shell 	*shell;
	t_var_list	*var_list;
	t_var		*var;
	size_t		i;

	fprintf(stderr, "\nDUMP VARIABLES\n");
	shell = shell_get();
	if (!shell)
	{
		error_print(error(ERR_SHELL_NOT_FOUND), "var_dump()", NULL, NULL);
		return ;
	}
	var_list = &shell->params.variables;
	i = 0;
	while (i < var_list->len)
	{
		var = &((t_var *)var_list->data)[i];
		var_dump_one(var);
		i++;
	}
}
