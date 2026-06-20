#include "shell_priv.h"
#include "options.h"
#include <stdlib.h>

void	shell_init(t_shell *shell)
{
	params_init(&shell->params);
	scanner_init(&shell->scanner);
	alias_init(&shell->alias);
	heredoc_init(&shell->heredoc);
	history_init(&shell->history);
	builder_init(&shell->builder);
	// TODO: runner_init(&shell->runner);
}

void	shell_free(t_shell **shell)
{
	params_free(&(*shell)->params);
	scanner_free(&(*shell)->scanner);
	alias_free(&(*shell)->alias);
	heredoc_free(&(*shell)->heredoc);
	history_free(&(*shell)->history);
	builder_free(&(*shell)->builder);
	// TODO: runner_free(&(*shell)->runner);
	free(*shell);
	*shell = NULL;
	shell_set(NULL);
}

void	shell_exit(t_error error)
{
	t_shell	*shell;

	shell = shell_get();
	(void)history_save();	// TODO: print error
	if (shell)
		shell_free(&shell);
	exit((int)error.type);
}

void	shell_exit_on_veof(void)
{
	if (!option_is_active(OPT_INTERACTIVE))
		return ;
	if (option_is_active(OPT_IGNOREEOF))
		return ;
	shell_exit(error(ERR_NO));
}
