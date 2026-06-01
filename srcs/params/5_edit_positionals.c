#include "shell.h"

t_error	params_push_positionals(t_positionals *src)
{
	t_shell		*shell;

	shell = shell_get();
	if (!shell)
		return (ERR_SHELL_NOT_FOUND);
	return (positionals_push(&shell->params.positionals, src));
}

t_error	params_shift_positionals(size_t n)
{
	t_shell		*shell;

	shell = shell_get();
	if (!shell)
		return (ERR_SHELL_NOT_FOUND);
	return (positionals_shift(&shell->params.positionals, n));
}

t_error	params_replace_positionals(t_positionals *src)
{
	t_shell		*shell;

	shell = shell_get();
	if (!shell)
		return (ERR_SHELL_NOT_FOUND);
	return (positionals_replace(&shell->params.positionals, src));
}

t_error	params_pop_positionals(void)
{
	t_shell		*shell;

	shell = shell_get();
	if (!shell)
		return (ERR_SHELL_NOT_FOUND);
	return (positionals_pop(&shell->params.positionals));
}
