#include "shell.h"
#include <stdlib.h>
#include <unistd.h>

static t_shell	*shell_get(t_shell *addr)
{
	static t_shell	*shell = NULL;

	if (addr)
		shell = addr;
	return (shell);
}

static void	shell_init(t_shell *shell)
{
	// TODO: shell_state_init(&shell->state);
	var_init_all(&shell->variables);
	// TODO: fun_init(&shell->functions);
	// TODO: lexer_init(&shell->lexer);
	builder_init(&shell->builder);
	// TODO: runner_init(&shell->runner);
}

static t_error	shell_load(t_shell *shell, char **envp)
{
	t_error	error;
	error = var_load_all(&shell->variables, envp);
	if (error != ERR_NO)
		return (error);
	error = builder_load(&shell->builder);
	if (error != ERR_NO)
		return (error);
	// TODO
	return (ERR_NO);
}

static void	shell_free(t_shell *shell)
{
	// TODO: shell_state_free(&shell->state);
	var_free_all(&shell->variables);
	// TODO: fun_free(&shell->functions);
	// TODO: lexer_free(&shell->lexer);
	builder_free(&shell->builder);
	// TODO: runner_free(&shell->runner);
}

/*
4. Initialize shell state parameters
	- $- = current option flags		(state.options)
		- i from isatty()
		- others from argv
	- $? = 0						(state.params.last_status)
	- $$ = pid of invoked shell		(state.params.shell_pid)
	- $0 = shell/script name		(????)

5. If interactive and ENV is set
	- expand ENV
	- read/tokenize/parse/execute that file before interactive commands
*/

t_error	shell_start(int argc, char **argv, char **envp, t_shell *parent_shell)
{
	t_shell	*shell;
	t_error	error;

	(void)argc;
	(void)argv;
	(void)parent_shell;
	shell = malloc(sizeof(*shell));
	if (!shell)
	{
		// TODO: error message
		return (ERR_LIBC);
	}
	shell_get(shell);
	shell_init(shell);
	error = shell_load(shell, envp);
	if (error != ERR_NO)
	{
		// TODO: print error message
		shell_free(shell);
		return (error);
	}
	// TODO: if subshell => set PPID at same value than parent shell (or give is_subshell as arg to var_load_all())
	// TODO: shell_state_load(&shell->state, argc, argv, envp);
	// if interactive => Process ENV
	// Process input
	shell_free(shell);
	return (ERR_NO);
}
