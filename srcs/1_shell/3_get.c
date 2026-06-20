#include "shell.h"

t_alias	*shell_get_alias(void)
{
	t_shell *shell;

	shell = shell_get();
	if (!shell)
		return (NULL);
	return (&shell->alias);
}

t_builder	*shell_get_builder(void)
{
	t_shell *shell;

	shell = shell_get();
	if (!shell)
		return (NULL);
	return (&shell->builder);
}

t_heredoc	*shell_get_heredoc(void)
{
	t_shell *shell;

	shell = shell_get();
	if (!shell)
		return (NULL);
	return (&shell->heredoc);
}

t_history	*shell_get_history(void)
{
	t_shell *shell;

	shell = shell_get();
	if (!shell)
		return (NULL);
	return (&shell->history);
}

t_params	*shell_get_params(void)
{
	t_shell *shell;

	shell = shell_get();
	if (!shell)
		return (NULL);
	return (&shell->params);
}

t_runner	*shell_get_runner(void)
{
	t_shell *shell;

	shell = shell_get();
	if (!shell)
		return (NULL);
	return (&shell->runner);
}

t_scanner	*shell_get_scanner(void)
{
	t_shell *shell;

	shell = shell_get();
	if (!shell)
		return (NULL);
	return (&shell->scanner);
}
