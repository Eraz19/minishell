#include "variables.h"
# include <stdio.h>	// TODO: tmp debug

// Errors can be ERR_VAR_NOT_FOUND / ERR_VAR_READ_ONLY / ERR_LIBC.
static t_error	process_variable(
	t_var_list	*variables,
	const char *name,
	const char *value)
{
	t_error	error;
	size_t	var_index;

	error = var_set(variables, name, value);
	if (error == ERR_VAR_INVALID_NAME)
		return (ERR_NO);
	else if (error != ERR_NO)
		return (error);
	if (!var_find(variables, name, &var_index))
		return (ERR_VAR_NOT_FOUND);
	((t_var *)variables->data)[var_index].export = true;
	printf("+ '%s' = '%s'\n", name, value);
	return (ERR_NO);
}

/*
1. Load envp variables with valid shell names
	- exported = true
	- readonly = false
	- invalid names: do not initialize shell variables from them
*/
t_error	var_load_envp(t_var_list *variables, char **envp)
{
	size_t	i;
	char	*name;
	char	*value;
	t_error	error;

	if (!envp)
		return (ERR_NO);
	i = 0;
	while (envp[i])
	{
		error = var_split(envp[i++], &name, &value);
		if (error == ERR_VAR_MISSING_EQUAL)
			continue ;
		if (error != ERR_NO)
			return (error);
		error = process_variable(variables, name, value);
		if (error != ERR_NO)
			return (error);
	}
	return (ERR_NO);
}
