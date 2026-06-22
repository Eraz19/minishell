#include "shell.h"

t_error	params_set_variable(
	const char *name,
	const char *value,
	bool export,
	bool readonly)
{
	return (var_set(name, value, export, readonly));
}

t_error	params_unset_variable(const char *name)
{
	return (var_unset(name));
}

t_error	params_set_last_bg_pid(pid_t value)
{
	t_params	*params;

	params = shell_get_params();
	if (!params)
		return (error(ERR_SHELL_NOT_FOUND));
	specials_set_last_bg_pid(&params->specials, value);
	return (error(ERR_NO));
}

t_error	params_set_last_status(int value)
{
	t_params	*params;

	params = shell_get_params();
	if (!params)
		return (error(ERR_SHELL_NOT_FOUND));
	specials_set_last_status(&params->specials, value);
	return (error(ERR_NO));
}

t_error	params_set_option(t_option option, bool on)
{
	t_params	*params;

	params = shell_get_params();
	if (!params)
		return (error(ERR_SHELL_NOT_FOUND));
	option_set(&params->options, option, on);
	return (error(ERR_NO));
}
