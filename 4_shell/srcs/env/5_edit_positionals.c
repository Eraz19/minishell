#include "shell.h"
#include <assert.h>	// DEBUG

t_error	env_push_positionals(t_positionals *src)
{
	t_params	*params;

	assert(src != NULL);
	params = shell_get_params();
	if (!params)
		return (error(ERR_SHELL_NOT_FOUND));
	return (positionals_push(&params->positionals_stack, src));
}

t_error	env_shift_positionals(size_t n)
{
	t_params	*params;

	params = shell_get_params();
	if (!params)
		return (error(ERR_SHELL_NOT_FOUND));
	return (positionals_shift(&params->positionals_stack, n));
}

t_error	env_replace_positionals(t_positionals *src)
{
	t_params	*params;

	assert(src != NULL);
	params = shell_get_params();
	if (!params)
		return (error(ERR_SHELL_NOT_FOUND));
	return (positionals_replace(&params->positionals_stack, src));
}

t_error	env_pop_positionals(void)
{
	t_params	*params;

	params = shell_get_params();
	if (!params)
		return (error(ERR_SHELL_NOT_FOUND));
	return (positionals_pop(&params->positionals_stack));
}
