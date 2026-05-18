#include "shell.h"

// @ret ERR_NO / ERR_SHELL_NOT_FOUND / ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY
// / ERR_LIBC.
t_error	params_set_variable(const char *name, const char *value)
{
	t_shell		*shell;

	shell = shell_get();
	if (!shell)
		return (ERR_SHELL_NOT_FOUND);
	return (var_set(&shell->params.variables, name, value));
}

// @ret ERR_NO / ERR_SHELL_NOT_FOUND / ERR_VAR_NOT_FOUND.
t_error	params_set_last_bg_pid(pid_t value)
{
	t_shell		*shell;

	shell = shell_get();
	if (!shell)
		return (ERR_SHELL_NOT_FOUND);
	return (specials_set(&shell->params.specials, '!', (long)value));
}

// @ret ERR_NO / ERR_SHELL_NOT_FOUND / ERR_VAR_NOT_FOUND.
t_error	params_set_last_status(long value)
{
	t_shell		*shell;

	shell = shell_get();
	if (!shell)
		return (ERR_SHELL_NOT_FOUND);
	return (specials_set(&shell->params.specials, '?', value));
}

// @ret ERR_NO / ERR_SHELL_NOT_FOUND.
t_error	params_set_option(t_option option, bool on)
{
	t_shell		*shell;

	shell = shell_get();
	if (!shell)
		return (ERR_SHELL_NOT_FOUND);
	option_set(&shell->params.options, option, on);
	return (ERR_NO);
}
