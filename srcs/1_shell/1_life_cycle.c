#include "shell_priv.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
# include <stdio.h>	// TODO: tmp debug

void	shell_init(t_shell *shell)
{
	params_init(&shell->params);
	// TODO: fun_init(&shell->functions);
	// TODO: lexer_init(&shell->lexer);
	builder_init(&shell->builder);
	// TODO: runner_init(&shell->runner);
}

void	shell_free(t_shell **shell)
{
	params_free(&(*shell)->params);
	// TODO: fun_free(&(*shell)->functions);
	// TODO: lexer_free(&(*shell)->lexer);
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
