#include "shell.h"
#include "posix_helpers.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void	shell_init(t_shell *shell)
{
	// TODO: shell_state_init(&shell->state);
	var_init_all(&shell->variables);
	// TODO: fun_init(&shell->functions);
	// TODO: lexer_init(&shell->lexer);
	builder_init(&shell->builder);
	// TODO: runner_init(&shell->runner);
}

// parent_shell can be NULL.
static t_error	shell_load(t_shell *shell, char **envp, t_shell *parent_shell)
{
	t_error	error;
	char	*parent_shell_ppid;

	parent_shell_ppid = NULL;
	if (parent_shell)
	{
		error = var_get(&parent_shell->variables, "PPID", &parent_shell_ppid);
		if (error != ERR_NO)
			return (error);
	}
	error = var_load_all(&shell->variables, envp, parent_shell_ppid);
	if (error != ERR_NO)
		return (error);
	// TODO: expand variables (inside variable module which should call expander module to perform expansions ??)
	// TODO: shell_state_load(&shell->state, argc, argv, envp);
	error = builder_load(&shell->builder);
	if (error != ERR_NO)
		return (error);
	// TODO
	return (ERR_NO);
}

static void	shell_free(t_shell *shell)
{
	var_free_all(&shell->variables);
	// TODO: shell_state_free(&shell->state);
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
t_error	shell_start(int argc, char **argv, char **envp, t_shell *parent)
{
	static const char	message[] = ": unable to malloc shell data struct: ";
	const char			*details;
	t_shell	*shell;
	t_error	error;

	(void)argc;
	(void)argv;
	shell = malloc(sizeof(*shell));
	if (!shell)
	{
		details = strerror(errno);
		(void)posix_write(STDERR_FILENO, argv[0], str_len(argv[0]));
		(void)posix_write(STDERR_FILENO, message, str_len(message));
		(void)posix_write(STDERR_FILENO, details, str_len(details));
		return (ERR_LIBC);
	}
	shell_init(shell);
	shell_set(shell);
	error = shell_load(shell, envp, parent);
	if (error != ERR_NO)
	{
		// TODO: print error message
		shell_free(shell);
		return (error);
	}
	// if interactive => Process ENV
	// Process input
	shell_free(shell);
	return (ERR_NO);
}
