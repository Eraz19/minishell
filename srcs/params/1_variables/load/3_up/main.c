#include "variables.h"
#include <stdlib.h>
#include <unistd.h>
# include <stdio.h>	// TODO: tmp debug

// Errors can be ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY / ERR_LIBC.
static t_error	var_init_target_up(
	t_var_list *variables,
	const char *name,
	const char *value)
{
	t_error	error;
	char	*current_value;

	error = var_get(variables, name, &current_value);
	if (error == ERR_NO)
	{
		free(current_value);
		return (ERR_NO);
	}
	if (error == ERR_VAR_NOT_FOUND)
		error = var_set(variables, name, value);
	if (error == ERR_NO)
		printf("-> '%s' has been set to '%s'\n", name, value);
	return (error);
}

/*
3. Initialize [UP] defaults if you support User Portability Utilities
	- PS1 = "$ " if absent
	- PS2 = "> " if absent
	- PS4 = "+ " if absent
*/
t_error	var_load_up(t_var_list *variables)
{
	t_error	error;

	error = var_init_target_up(variables, "PS1", "$ ");
	if (error != ERR_NO)
		return (error);
	error = var_init_target_up(variables, "PS2", "> ");
	if (error != ERR_NO)
		return (error);
	return (var_init_target_up(variables, "PS4", "+ "));
}
