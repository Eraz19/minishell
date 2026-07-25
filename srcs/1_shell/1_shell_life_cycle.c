#include "shell_priv.h"
#include "lr_machine.h"
#include "runner.h"
#include <stdlib.h>
# include <assert.h>

void	shell_init(t_shell *shell)
{
	shell->is_subshell = false;
	params_init(&shell->params);
	lr_machine_init(&shell->machine);
	history_init(&shell->history);
	alias_init(&shell->alias);
	shell->runner = NULL;
	shell->last_runner = NULL;
}

void	shell_clear(void)
{
	t_shell	*shell;

	shell = shell_get();
	assert(shell != NULL);
	shell->is_subshell = false;
	params_clear(&shell->params);
	alias_clear(&shell->alias);
	if (shell->runner != NULL)
		runner_free(shell->runner);
}

void	shell_free(t_shell *shell)
{
	params_free(&shell->params);
	lr_machine_free(&shell->machine);
	history_free(&shell->history);
	alias_free(&shell->alias);
	if (shell->runner != NULL)
		runner_free(shell->runner);
	free(shell);
	shell_set(NULL);
}

void	shell_free_void(void)
{
	t_shell	*shell;

	shell = shell_get();
	if (shell != NULL)
		shell_free(shell);
}
