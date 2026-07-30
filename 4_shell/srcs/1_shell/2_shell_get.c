#include "shell.h"
# include <assert.h>	// DEBUG

t_history	*shell_get_history(void)
{
	t_shell *shell;

	shell = shell_get();
	assert(shell != NULL);
	return (&shell->history);
}

t_params	*shell_get_params(void)
{
	t_shell *shell;

	shell = shell_get();
	assert(shell != NULL);
	return (&shell->params);
}

const t_lr_tables	*shell_get_lr_tables(void)
{
	t_shell	*shell;

	shell = shell_get();
	assert(shell != NULL);
	return (&shell->lr_tables);
}
