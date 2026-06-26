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
	runner_init(&shell->runner);
}

void	shell_free(void)
{
	t_shell	*shell;

	shell = shell_get();
	if (!shell)
		return ;
	params_free(&shell->params);
	scanner_free(&shell->scanner);
	alias_free(&shell->alias);
	heredoc_free(&shell->heredoc);
	history_free(&shell->history);
	builder_free(&shell->builder);
	runner_free(&shell->runner);
	free(shell);
	shell_set(NULL);
}

bool	shell_should_exit_on_veof(void)
{
	if (!option_is_active(OPT_INTERACTIVE))
		return (false);
	if (option_is_active(OPT_IGNOREEOF))
		return (false);
	return (true);
}
