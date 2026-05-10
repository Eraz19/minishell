#include "shell.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void	shell_init(t_shell *shell)
{
	params_init(&shell->params);
	// TODO: fun_init(&shell->functions);
	// TODO: lexer_init(&shell->lexer);
	builder_init(&shell->builder);
	// TODO: runner_init(&shell->runner);
}

static t_error	shell_load(t_shell *shell, int argc, char **argv, char **envp)
{
	t_error	error;

	error = params_load(&shell->params, argc, argv, envp);
	if (error != ERR_NO)
		return (error);
	// TODO: prepare STDIN (si stdin est un FIFO ou un terminal configuré en non-blocking, sh doit le remettre en blocking mode, et cet état doit rester en vigueur quand la commande se termine.)
	// TODO: load functions module
	// TODO: load lexer module
	error = builder_load(&shell->builder);
	if (error != ERR_NO)
		return (error);
	// TODO: load runner module
	// TODO: expand variables (inside variable module which should call expander module to perform expansions ??)
	return (ERR_NO);
}

static void	shell_free(t_shell *shell)
{
	params_free(&shell->params);
	// TODO: fun_free(&shell->functions);
	// TODO: lexer_free(&shell->lexer);
	builder_free(&shell->builder);
	// TODO: runner_free(&shell->runner);
}

void	shell_exit(t_error error)
{
	t_shell	*shell;

	shell = shell_get();
	if (shell)
		shell_free(shell);
	exit((int)error);
}

/*
4. Initialize shell state parameters
	- $? = 0						(state.params.last_status)
	- $$ = pid of invoked shell		(state.params.shell_pid)
	- $0 = shell/script name		(????)

5. If interactive and ENV is set
	- expand ENV
	- read/tokenize/parse/execute that file before interactive commands
*/
t_error	shell_start(int argc, char **argv, char **envp, t_shell *parent)
{
	static const char	message[] = ": unable to malloc shell data struct: ";
	t_shell				*shell;
	t_error				error;

	shell = malloc(sizeof(*shell));
	if (!shell)
		return (error_print(NULL, message, ERR_LIBC), ERR_LIBC);
	shell_init(shell);
	shell_set(shell);
	shell->params.parent_shell = parent;
	error = shell_load(shell, argc, argv, envp);
	if (error != ERR_NO)
		return (shell_free(shell), error);
	if (option_is_active(shell->params.options, OPT_INTERACTIVE))
	{
		// TODO: if interactive => Expand ENV => Process ENV
	}
	// TODO: Process input
	shell_free(shell);
	return (error);
}
