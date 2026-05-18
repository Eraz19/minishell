#include "shell_priv.h"
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
# include "logs.h"	// TODO: tmp debug

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
			print_pass("stdin is not a fifo: did not set it to blocking mode\n");
			return (ERR_NO);
		}
	}
	enabled = 0;
	if (ioctl(STDIN_FILENO, FIONBIO, &enabled) == -1)
	{
		error_print(NULL, "Unable to set stdin to blocking mode", ERR_LIBC);
		return (ERR_LIBC);
	}
	print_pass("stdin has been set to blocking mode\n");
	return (ERR_NO);
}

static t_error	shell_load(t_shell *shell, int argc, char **argv, char **envp)
{
	t_error	error;

	print_title("shell_load()");
	error = params_load(&shell->params, argc, argv, envp);
	if (error != ERR_NO)
		return (error);
	// TODO: history_load();
	print_warn("History not implemented yet             => skipping loading\n");
	// TODO: fun_load(&shell->functions);
	print_warn("Functions not implemented yet           => skipping loading\n");
	// TODO: scanner_load(&shell->lexer);
	print_warn("Scanner not implemented yet             => skipping loading\n");
	error = builder_load(&shell->builder);
	if (error != ERR_NO)
		return (error);
	// TODO: runner_load(&shell->runner);
	print_warn("Runner not implemented yet              => skipping loading\n");
	error = shell_set_stdin_to_blocking();
	if (error != ERR_NO)
		return (error);
	print_result("shell_load()");
	return (ERR_NO);
}

// @ret ERR_NO / ERR_LIBC.
static t_error	shell_exec_env(t_shell *shell)
{
	t_error	error;
	char	*raw_env;

	print_title("shell_exec_env()");
	if (!option_is_active_in(shell->params.options, OPT_INTERACTIVE))
		return (ERR_NO);
	error = params_get("ENV", &raw_env);
	if (error == ERR_LIBC)
		return (error);
	if (!raw_env)
		return (ERR_NO);
	if (option_is_active(OPT_STDIN_INPUT))
	{
		print_warn("Expander and Runner not implemented yet => skipping ENV execution\n");
		// TODO: expand ENV
		// TODO: exec ENV
	}
	print_result("shell_exec_env()");
	return (ERR_NO);
}

t_error	shell_start(int argc, char **argv, char **envp, t_shell *parent)
{
	static const char	message[] = ": unable to malloc shell data struct: ";
	t_shell				*shell;
	t_error				error;

	print_start(99, "shell_start()");
	shell = malloc(sizeof(*shell));
	if (!shell)
		return (error_print(NULL, message, ERR_LIBC), ERR_LIBC);
	print_title("shell_init()");
	shell_init(shell);
	print_result("shell_init()");
	shell_set(shell);
	shell->params.parent_shell = parent;
	error = shell_load(shell, argc, argv, envp);
	if (error != ERR_NO)
		shell_exit(error);
	error = shell_exec_env(shell);
	if (error != ERR_NO)
		return (error);
	// TODO: runner_run(t_shell *shell);
	print_warn("Runner not implemented yet => skipping execution loop\n");
	print_stop();
	shell_exit(error);
	return (ERR_NO);
}
