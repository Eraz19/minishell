#include "variables_priv.h"
#include <stdlib.h>
# include "logs.h"	// TODO: tmp debug

// @ret ERR_SHELL_NOT_FOUND / ERR_VAR_READ_ONLY / ERR_LIBC.
static t_error	process_variable(
	const char *name,
	const char *value)
{
	t_error	error;

	error = var_set(name, value, true, false);
	if (error == ERR_VAR_INVALID_NAME)
		return (ERR_NO);
	if (error == ERR_NO)
		print_pass("'%s' = '%s'\n", name, value);
	return (error);
}

/*
1. Load envp variables with valid shell names
	- exported = true
	- readonly = false
	- invalid names: do not initialize shell variables from them
*/
t_error	var_load_envp(char **envp)
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
		error = process_variable(name, value);
		free(name);
		free(value);
		if (error != ERR_NO)
			return (error);
	}
	return (ERR_NO);
}
