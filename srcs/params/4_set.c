#include "shell.h"
# include <assert.h>	// DEBUG
# include "logs.h"
# include <stdio.h>

// TODO: refactor
static inline t_error	params_get_struct(t_params **dst)
{
	t_error	err;

	*dst = shell_get_params();
	if (*dst == NULL)
	{
		err = error_print(error(ERR_SHELL_NOT_FOUND), "params", NULL, NULL);
		err.type = ERR_INTERNAL;
		return (err);
	}
	return (error(ERR_NO));
}

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

void	params_set_last_status_in(t_params *params, int value)
{
	specials_set_last_status(&params->specials, value);
	fprintf(stderr, "%s[PARAMS] $? = %i%s\n", YELLOW, value, NC);
}

t_error	params_set_last_status(int value)
{
	t_params	*params;
	t_error		err;

	err = params_get_struct(&params);
	if (err.type)
		return (err);
	params_set_last_status_in(params, value);
	return (err);
}

t_error	params_set_option(t_option option, bool on)
{
	t_params	*params;
	t_error		err;

	err = params_get_struct(&params);
	if (err.type)
		return (err);
	option_set(&params->options, option, on);
	return (err);
}
