#include "variables.h"
#include <stdlib.h>
#include <unistd.h>
# include "logs.h"	// TODO: tmp debug

// @ret ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY / ERR_LIBC.
static t_error	var_init_target_up(const char *name, const char *value)
{
	t_error	err;
	char	*current_value;

	err = var_get(name, &current_value);
	if (err.type == ERR_NO)
	{
		free(current_value);
		return (error(ERR_NO));
	}
	if (err.type == ERR_VAR_NOT_FOUND)
		err = var_set(name, value, false, false);
	if (err.type == ERR_NO)
		print_pass("'%s' has been set to '%s'\n", name, value);
	return (err);
}

/*
3. Initialize [UP] defaults if you support User Portability Utilities
	- PS1 = "$ " if absent
	- PS2 = "> " if absent
	- PS4 = "+ " if absent
*/
t_error	var_load_up(void)
{
	t_error	err;

	err = var_init_target_up("PS1", "$ ");
	if (err.type != ERR_NO)
		return (err);
	err = var_init_target_up("PS2", "> ");
	if (err.type != ERR_NO)
		return (err);
	return (var_init_target_up("PS4", "+ "));
}
