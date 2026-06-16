#include "variables.h"
#include "utils.h"
#include <stdlib.h>
# include "logs.h"	// TODO: tmp debug

// @ret ERR_SHELL_NOT_FOUND / ERR_VAR_READ_ONLY / ERR_LIBC.
static t_error	process_variable(
	const char *name,
	const char *value)
{
	t_error	err;

	err = var_set(name, value, true, false);
	if (err.type == ERR_VAR_INVALID_NAME)
		return (error(ERR_NO));
	if (err.type == ERR_NO)
		print_pass("'%s' = '%s'\n", name, value);
	return (err);
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
	t_error	err;

	if (!envp)
		return (error(ERR_NO));
	i = 0;
	while (envp[i])
	{
		err = assignment_split(envp[i++], &name, &value);
		if (err.type != ERR_NO)
			return (err);
		if (!value)
			continue ;
		err = process_variable(name, value);
		free(name);
		free(value);
		if (err.type != ERR_NO)
			return (err);
	}
	return (error(ERR_NO));
}
