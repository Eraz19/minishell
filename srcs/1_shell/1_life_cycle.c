#include "shell_priv.h"
#include "options.h"
#include <stdlib.h>

void	shell_init(t_shell *shell)
{
	params_init(&shell->params);
	// TODO: fun_init(&shell->functions);
	// TODO: scanner_init(&shell->lexer);
	builder_init(&shell->builder);
	// TODO: runner_init(&shell->runner);
}

void	shell_free(t_shell **shell)
{
	params_free(&(*shell)->params);
	// TODO: fun_free(&(*shell)->functions);
	// TODO: scanner_free(&(*shell)->lexer);
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
	// TODO: history_save();
	if (shell)
		shell_free(&shell);
	exit((int)error);
}

void	shell_exit_on_veof(void)
{
	if (!option_is_active(OPT_INTERACTIVE))
		return ;
	if (option_is_active(OPT_IGNOREEOF))
		return ;
	shell_exit(ERR_NO);
}
