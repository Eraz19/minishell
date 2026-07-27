#include "env.h"
#include "shell.h"
# include <assert.h>	// DEBUG

t_error env_print(t_env_print_mode mode)
{
	assert(mode == ENV_PRINT_EXPORT || mode == ENV_PRINT_READONLY || mode == ENV_PRINT_SET);
	return var_print((t_var_print_mode)mode);
}

t_error	env_print_one_alias(const char *name)
{
	t_params	*params;

	params = shell_get_params();
	assert(params != NULL);
	return (alias_print_one(&params->alias, name));
}
