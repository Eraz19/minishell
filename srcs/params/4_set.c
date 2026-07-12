#include "shell.h"
# include <assert.h>	// DEBUG

t_error	params_set_variable(
	const t_string *name,
	const t_string *value,
	bool export,
	bool readonly)
{
	assert(name != NULL);
	assert(value != NULL);
	return (var_set(name, value, export, readonly));
}

t_error	params_unset_variable(const t_string *name)
{
	assert(name != NULL);
	return (var_unset(name));
}

t_error	params_mark_async_started(pid_t value)
{
	t_params	*params;

	params = shell_get_params();
	if (!params)
		return (error(ERR_SHELL_NOT_FOUND));
	specials_set_last_bg_pid(&params->specials, value);
	specials_set_last_status(&params->specials, 0);
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
