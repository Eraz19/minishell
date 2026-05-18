#include "shell_priv.h"
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
# include <stdio.h>	// TODO: tmp debug

// TODO: move to runner/executor (because it will use it after each command execution)
// ERR_NO / ERR_LIBC
t_error	shell_set_stdin_to_blocking(void)
{
	int			enabled;
	struct stat	stat_buff;
	bool		is_a_terminal;
	bool		is_fifo;
	
	is_a_terminal = isatty(STDIN_FILENO);
	if (!is_a_terminal)
	{
		if (fstat(STDIN_FILENO, &stat_buff) != 0)
		{
			error_print(NULL, "unable to check if stdin is FIFO", ERR_LIBC);
			return (ERR_LIBC);
		}
		is_fifo = S_ISFIFO(stat_buff.st_mode);
		if (!is_fifo)
		{
			printf("-> stdin is not a fifo: did not set it to blocking mode\n");
			return (ERR_NO);
		}
	}
	enabled = 0;
	if (ioctl(STDIN_FILENO, FIONBIO, &enabled) == -1)
	{
		error_print(NULL, "Unable to set stdin to blocking mode", ERR_LIBC);
		return (ERR_LIBC);
	}
	printf("-> stdin has been set to blocking mode\n");
	return (ERR_NO);
}

static t_error	shell_load(t_shell *shell, int argc, char **argv, char **envp)
{
	t_error	error;

	error = params_load(&shell->params, argc, argv, envp);
	if (error != ERR_NO)
		return (error);
	// TODO: history_load();
	printf("👉 History not implemented yet             => skipping loading\n");
	// TODO: fun_load(&shell->functions);
	printf("👉 Functions not implemented yet           => skipping loading\n");
	// TODO: scanner_load(&shell->lexer);
	printf("👉 Scanner not implemented yet             => skipping loading\n");
	error = builder_load(&shell->builder);
	if (error != ERR_NO)
		return (error);
	// TODO: runner_load(&shell->runner);
	printf("👉 Runner not implemented yet              => skipping loading\n");
	return (shell_set_stdin_to_blocking());
}

// @ret ERR_NO / ERR_LIBC.
static t_error	shell_exec_env(t_shell *shell)
{
	t_error	error;
	char	*raw_env;

	if (!option_is_active_in(shell->params.options, OPT_INTERACTIVE))
		return (ERR_NO);
	error = params_get("ENV", &raw_env);
	if (error == ERR_LIBC)
		return (error);
	if (!raw_env)
		return (ERR_NO);
	if (option_is_active(OPT_STDIN_INPUT))
	{
		printf("👉 Expander and Runner not implemented yet => skipping ENV execution\n");
		// TODO: expand ENV
		// TODO: exec ENV
	}
	return (ERR_NO);
}

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
		shell_exit(error);
	error = shell_exec_env(shell);
	if (error != ERR_NO)
		return (error);
	// TODO: runner_run(t_shell *shell);
	printf("👉 Runner not implemented yet => skipping execution loop\n");
	printf("⚠️ Exiting\n");
	shell_exit(error);
	return (error);
}
