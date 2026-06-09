#include "shell.h"

t_params	*shell_get_params(void)
{
	t_shell *shell;

	shell = shell_get();
	if (!shell)
		return (NULL);
	return (&shell->params);
}

t_history	*shell_get_history(void)
{
	t_shell *shell;

	shell = shell_get();
	if (!shell)
		return (NULL);
	return (&shell->history);
}

t_scanner	*shell_get_scanner(void)
{
	t_shell *shell;

	shell = shell_get();
	if (!shell)
		return (NULL);
	return (&shell->scanner);
}

t_builder	*shell_get_builder(void)
{
	t_shell *shell;

	shell = shell_get();
	if (!shell)
		return (NULL);
	return (&shell->builder);
}

t_runner	*shell_get_runner(void)
{
	t_shell *shell;

	shell = shell_get();
	if (!shell)
		return (NULL);
	return (&shell->runner);
}
