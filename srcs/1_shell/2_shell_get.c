#include "shell.h"
# include <assert.h>	// DEBUG

#define NO_SHELL	"shell not found"

t_alias	*shell_get_alias(void)
{
	t_shell *shell;

	shell = shell_get();
	assert(shell != NULL);
	return (&shell->alias);
}

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

const t_lr_machine	*shell_get_lr_machine(void)
{
	t_shell	*shell;

	shell = shell_get();
	assert(shell != NULL);
	return (&shell->machine);
}
