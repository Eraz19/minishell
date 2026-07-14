#include "params.h"
#include "shell.h"

t_error	params_set_function(t_ast_function_def *function_def)
{
	t_params	*params;

	params = shell_get_params();
	if (params == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	return (function_set(&params->functions, function_def));
}

t_error	params_get_function(const char *name, t_function **out)
{
	t_params	*params;

	params = shell_get_params();
	if (params == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	return (function_get(&params->functions, name, out));
}

t_error	params_unset_function(const char *name)
{
	t_params	*params;

	params = shell_get_params();
	if (params == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	function_unset(&params->functions, name);
	return (error(ERR_NO));
}

void	params_stop_function(t_function **function)
{
	function_stop(function);
}
