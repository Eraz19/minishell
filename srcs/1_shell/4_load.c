#include "shell.h"
#include <sys/ioctl.h>
#include <unistd.h>
# include "logs.h"	// DEBUG

// ⚠️ TODO: move to runner/executor (because it will use it after each command execution)
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
			return (error_print(error_sys(), "unable to check if stdin is FIFO", NULL, NULL));
		is_fifo = S_ISFIFO(stat_buff.st_mode);
		if (!is_fifo)
		{
			print_pass("stdin is not a fifo: did not set it to blocking mode\n");
			return (error(ERR_NO));
		}
	}
	enabled = 0;
	if (ioctl(STDIN_FILENO, FIONBIO, &enabled) == -1)
		return (error_print(error_sys(), "Unable to set stdin to blocking mode", NULL, NULL));
	print_pass("stdin has been set to blocking mode\n");
	return (error(ERR_NO));
}

static t_error	shell_load_scanner(t_shell *shell)
{
	t_scanner_mode	mode;

	if (option_is_active(OPT_STDIN_INPUT))
		mode = SCAN_STDIN;
	else if (option_is_active(OPT_CMD_STRING))
		mode = SCAN_STRING;
	else
		mode = SCAN_FILE;
	return (scanner_load(&shell->scanner, mode, shell->params.specials.source));
}

t_error	shell_load(t_shell *shell, int argc, char **argv, char **envp)
{
	t_error	err;

	print_title("shell_load()");
	err = params_load(&shell->params, argc, argv, envp);
	if (err.type == ERR_NO)
		err = history_load(&shell->history);
	if (err.type == ERR_NO)
		err = shell_load_scanner(shell);
	if (err.type == ERR_NO)
		err = builder_load(&shell->builder);
	if (err.type == ERR_NO)
		print_warn("Runner not implemented yet              => skipping loading\n");	// TODO: runner_load(&shell->runner);
	if (err.type == ERR_NO)
		err = shell_set_stdin_to_blocking();
	if (err.type != ERR_NO)
		return (err);
	print_result("shell_load()");
	return (error(ERR_NO));
}
