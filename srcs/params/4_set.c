#include "shell.h"

t_error	params_set_variable(const char *name, const char *value)
{
	t_shell		*shell;

	shell = shell_get();
	if (!shell)
		return (ERR_SHELL_NOT_FOUND);
	return (var_set(&shell->params.variables, name, value));
}

t_error	params_set_last_bg_pid(pid_t value)
{
	t_shell		*shell;

	shell = shell_get();
	if (!shell)
		return (ERR_SHELL_NOT_FOUND);
	specials_set_last_bg_pid(&shell->params.specials, value);
	return (ERR_NO);
}

t_error	params_set_last_status(int value)
{
	t_shell		*shell;

	shell = shell_get();
	if (!shell)
		return (ERR_SHELL_NOT_FOUND);
	specials_set_last_status(&shell->params.specials, value);
	return (ERR_NO);
}

t_error	params_set_option(t_option option, bool on)
{
	t_shell		*shell;

	shell = shell_get();
	if (!shell)
		return (ERR_SHELL_NOT_FOUND);
	option_set(&shell->params.options, option, on);
	return (ERR_NO);
}
