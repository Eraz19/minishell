#include "shell_priv.h"
#include "lr_machine.h"
#include <stdlib.h>

void	shell_init(t_shell *shell)
{
	shell->is_subshell = false;
	params_init(&shell->params);
	lr_machine_init(&shell->machine);
	history_init(&shell->history);
	alias_init(&shell->alias);
}

void	shell_free(t_shell *shell)
{
	params_free(&shell->params);
	lr_machine_free(&shell->machine);
	history_free(&shell->history);
	alias_free(&shell->alias);
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
