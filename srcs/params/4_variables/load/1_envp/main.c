#include "variables.h"
#include "utils.h"
#include <stdlib.h>
# include "logs.h"		// DEBUG
# include <assert.h>	// DEBUG

// @ret ERR_SHELL_NOT_FOUND / ERR_VAR_READ_ONLY / ERR_LIBC.
static inline t_error	process_entry(t_string *name, t_string *value)
{
	t_error	err;

	if (value->data == NULL)
		return (error(ERR_NO));
	err = var_set(name, value, true, false);
	if (err.type == ERR_VAR_INVALID_NAME)
		return (error(ERR_NO));
	if (err.type == ERR_NO)
		print_pass("'%s' = '%s'\n", name->data, value->data);
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
	size_t		i;
	t_string	name;
	t_string	value;
	t_error		err;

	if (!envp)
		return (error(ERR_NO));
	i = 0;
	err = error(ERR_NO);
	while (envp[i] && err.type == ERR_NO)
	{
		err = assignment_split(envp[i], &name, &value);
		if (err.type)
			return (err);
		err = process_entry(&name, &value);
		string_free(&name);
		string_free(&value);
		i++;
	}
	return (err);
}
