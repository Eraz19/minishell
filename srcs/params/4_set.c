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

t_error	params_unset_variable(const t_string *name)
{
	assert(name != NULL);
	return (var_unset(name));
}

void	params_set_last_status_in_priv(const char *caller, t_params *params, int value)
{
	if (str_cmp(caller, "runner_handle_syntax_errors") != 0
		&& str_cmp(caller, "runner_handle_read_errors") != 0
		&& str_cmp(caller, "params_set_last_status_priv") != 0)
	{
		fprintf(stderr, RED);
		(void)error_print(error(ERR_INTERNAL), __func__, "caller is not allowed", caller, NULL, NULL);
		fprintf(stderr, NC);
		assert(true == false);
	}
	specials_set_last_status(&params->specials, value);
	fprintf(stderr, "%s[PARAMS] $? = %i%s\n", YELLOW, value, NC);
}

t_error	params_set_last_status_priv(const char *caller, int value)
{
	t_params	*params;
	t_error		err;

	if (str_cmp(caller, "walk_pipeline") != 0)
	{
		fprintf(stderr, RED);
		err = error_print(error(ERR_INTERNAL), __func__, "caller is not allowed", caller, NULL, NULL);
		fprintf(stderr, NC);
		return (err);
	}
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
