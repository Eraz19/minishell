#include "shell.h"
#include <assert.h>	// DEBUG
#ifdef DEBUG_CMD
# include "logs.h"
#include <stdio.h>
#endif

// TODO: refactor
static inline t_error	env_get_struct(t_params **dst)
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

t_error	env_set_variable(
	const t_string *name,
	const t_string *value,
	bool export,
	bool readonly)
{
	t_error	err;

	assert(name != NULL);
	assert(value != NULL);
	err = var_set(name, value, export, readonly);
	if (err.type)
	{
		err = error_print(err, NULL, "%s", name->data, NULL);
		if (err.type != ERR_LIBC)
			err.type = ERR_POSIX_ASSIGNMENT;
	}
	return (err);
}

t_error	env_unset_variable(const t_string *name)
{
	assert(name != NULL);
	return (var_unset(name));
}

void	env_set_last_status_in(t_params *params, int value)
{
	specials_set_last_status(&params->specials, value);
#ifdef DEBUG_CMD
	fprintf(stderr, "%s[PARAMS] $? = %i%s\n", YELLOW, value, NC);
#endif
}

t_error	env_set_last_status(int value)
{
	t_params	*params;
	t_error		err;

	err = env_get_struct(&params);
	if (err.type)
		return (err);
	env_set_last_status_in(params, value);
	return (err);
}

t_error	env_set_option(t_option option, bool on)
{
	t_params	*params;
	t_error		err;

	err = env_get_struct(&params);
	if (err.type)
		return (err);
	option_set(&params->options, option, on);
	return (err);
}
