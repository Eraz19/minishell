#include "variables.h"
#include <stdlib.h>
#include <unistd.h>
# include "logs.h"	// TODO: tmp debug

// @ret ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY / ERR_LIBC.
static t_error	var_init_target_up(const char *name, const char *value)
{
	t_error	error;
	char	*current_value;

	error = var_get(name, &current_value);
	if (error == ERR_NO)
	{
		free(current_value);
		return (ERR_NO);
	}
	if (error == ERR_VAR_NOT_FOUND)
		error = var_set(name, value, false, false);
	if (error == ERR_NO)
		print_pass("'%s' has been set to '%s'\n", name, value);
	return (error);
}

/*
3. Initialize [UP] defaults if you support User Portability Utilities
	- PS1 = "$ " if absent
	- PS2 = "> " if absent
	- PS4 = "+ " if absent
*/
t_error	var_load_up(void)
{
	t_error	error;

	error = var_init_target_up("PS1", "$ ");
	if (error != ERR_NO)
		return (error);
	error = var_init_target_up("PS2", "> ");
	if (error != ERR_NO)
		return (error);
	return (var_init_target_up("PS4", "+ "));
}
