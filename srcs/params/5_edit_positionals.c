#include "shell.h"

t_error	params_push_positionals(t_positionals *src)
{
	t_params	*params;

	params = shell_get_params();
	if (!params)
		return (error(ERR_SHELL_NOT_FOUND));
	return (positionals_push(&params->positionals, src));
}

t_error	params_shift_positionals(size_t n)
{
	t_params	*params;

	params = shell_get_params();
	if (!params)
		return (error(ERR_SHELL_NOT_FOUND));
	return (positionals_shift(&params->positionals, n));
}

t_error	params_replace_positionals(t_positionals *src)
{
	t_params	*params;

	params = shell_get_params();
	if (!params)
		return (error(ERR_SHELL_NOT_FOUND));
	return (positionals_replace(&params->positionals, src));
}

t_error	params_pop_positionals(void)
{
	t_params	*params;

	params = shell_get_params();
	if (!params)
		return (error(ERR_SHELL_NOT_FOUND));
	return (positionals_pop(&params->positionals));
}
