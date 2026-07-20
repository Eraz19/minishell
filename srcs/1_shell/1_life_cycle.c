#include "shell_priv.h"
#include "runner.h"
#include "options.h"
#include "sig.h"
#include <stdlib.h>

void	shell_init(t_shell *shell)
{
	params_init(&shell->params);
	scanner_init(&shell->scanner);
	alias_init(&shell->alias, &shell->builder.parser);
	history_init(&shell->history);
	builder_init(&shell->builder, &shell->scanner);
	runner_init(&shell->runner, &shell->params.cmd_cache);
	shell->is_subshell = false;
}

t_error	shell_clear(t_shell *shell)
{
	params_clear(&shell->params);
	scanner_clear(&shell->scanner);
	alias_clear(&shell->alias);
	history_clear(&shell->history);
	builder_clear(&shell->builder);
	sig_clear();
	shell->is_subshell = false;
	return (runner_clear(&shell->runner));
}

void	shell_free(t_shell *shell)
{
	params_free(&shell->params);
	scanner_free(&shell->scanner);
	alias_free(&shell->alias);
	history_free(&shell->history);
	builder_free(&shell->builder);
	runner_free(&shell->runner);
	shell->is_subshell = false;
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

t_error		shell_should_exit_on_veof(void)
{
	bool	is_interactive;
	bool	ignore_eof;
	t_error	err;

	err = option_is_active(OPT_INTERACTIVE, &is_interactive);
	if (err.type == ERR_NO)
		err = option_is_active(OPT_IGNOREEOF, &ignore_eof);
	if (err.type == ERR_NO && is_interactive == true && ignore_eof == false)
		return (error(ERR_VEOF));
	return (err);
}
