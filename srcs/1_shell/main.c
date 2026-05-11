#include "shell_priv.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <unistd.h>
# include <stdio.h>	// TODO: tmp debug

// TODO: in which module ? (executor will need it!)
t_error	shell_set_stdin_to_blocking(void)
{
	int			enabled;
	struct stat	stat_buff;
	bool		is_a_terminal;
	bool		is_fifo;
	
	is_a_terminal = isatty(STDIN_FILENO);
	is_fifo = fstat(STDIN_FILENO, &stat_buff) == 0 && S_ISFIFO(stat_buff.st_mode);
	if (!is_a_terminal && !is_fifo)
		return (ERR_NO);
	enabled = 0;
	if (ioctl(STDIN_FILENO, FIONBIO, &enabled) == -1)
		return (error_print(NULL, NULL, ERR_UNABLE_TO_BLOCK_STDIN));
	return (ERR_NO);
}

static t_error	shell_load(t_shell *shell, int argc, char **argv, char **envp)
{
	t_error	error;

	error = params_load(&shell->params, argc, argv, envp);
	if (error != ERR_NO)
		return (error);
	// TODO: history_load();
	// TODO: fun_load(&shell->functions);
	// TODO: lexer_load(&shell->lexer);
	error = builder_load(&shell->builder);
	if (error != ERR_NO)
		return (error);
	// TODO: runner_load(&shell->runner);
	return (shell_set_stdin_to_blocking());
}

static t_error	shell_exec_env(t_shell *shell)
{
	char	*raw_env;

	if (!option_is_active_in(shell->params.options, OPT_INTERACTIVE))
		return (ERR_NO);
	raw_env = param_get("ENV");
	if (!raw_env)
		return (ERR_NO);
	if (raw_env[0] == '\0')
	{
		free(raw_env);
		return (ERR_NO);
	}
	// TODO: ⚠️ if interactive && ENV is set => Expand ENV => Process ENV
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

	// TODO: runner_run(t_shell *shell);
	shell_exit(error);
	return (error);
}
