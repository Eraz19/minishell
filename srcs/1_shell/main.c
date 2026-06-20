#include "shell_priv.h"
#include "history.h"
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
# include "logs.h"	// TODO: tmp debug

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

static t_error	shell_load(t_shell *shell, int argc, char **argv, char **envp)
{
	t_error	err;

	print_title("shell_load()");
	err = params_load(&shell->params, argc, argv, envp);
	if (err.type != ERR_NO)
		return (err);
	err = history_load(&shell->history);
	if (err.type != ERR_NO)
		return (err);
	// TODO: fun_load(&shell->functions);
	print_warn("Functions not implemented yet           => skipping loading\n");
	/*---------------------------------------*/
	if (option_is_active(OPT_STDIN_INPUT))
		err = scanner_load(&shell->scanner, SCAN_STDIN, shell->params.specials.source);
	else if (option_is_active(OPT_CMD_STRING))
		err = scanner_load(&shell->scanner, SCAN_STRING, shell->params.specials.source);
	else
		err = scanner_load(&shell->scanner, SCAN_FILE, shell->params.specials.source);
	if (err.type != ERR_NO)
		return (err);
	/*---------------------------------------*/
	print_warn("Scanner not implemented yet             => skipping loading\n");
	err = builder_load(&shell->builder);
	if (err.type != ERR_NO)
		return (err);
	// TODO: runner_load(&shell->runner);
	print_warn("Runner not implemented yet              => skipping loading\n");
	err = shell_set_stdin_to_blocking();
	if (err.type != ERR_NO)
		return (err);
	print_result("shell_load()");
	return (error(ERR_NO));
}

// @ret ERR_NO / ERR_LIBC.
static t_error	shell_exec_env(t_shell *shell)
{
	t_error	err;
	char	*raw_env;

	print_title("shell_exec_env()");
	if (!option_is_active_in(shell->params.options, OPT_INTERACTIVE))
		return (error(ERR_NO));
	err = params_get("ENV", &raw_env);
	if (err.type == ERR_LIBC)
		return (err);
	if (!raw_env)
		return (error(ERR_NO));
	if (option_is_active(OPT_STDIN_INPUT))
	{
		print_warn("Expander and Runner not implemented yet => skipping ENV execution\n");
		// TODO: expand ENV
		// TODO: exec ENV
	}
	print_result("shell_exec_env()");
	return (error(ERR_NO));
}

t_error	shell_start(int argc, char **argv, char **envp)
{
	static const char	message[] = ": unable to malloc shell data struct: ";
	t_shell				*shell;
	t_error				err;

	// print_start(99, "shell_start()");
	shell = malloc(sizeof(*shell));
	if (!shell)
		return (error_print(error_sys(), message, NULL, NULL));
	print_title("shell_init()");
	shell_init(shell);
	print_result("shell_init()");
	shell_set(shell);
	err = shell_load(shell, argc, argv, envp);
	if (err.type != ERR_NO)
		shell_exit(err);
	err = shell_exec_env(shell);
	if (err.type != ERR_NO)
		return (err);
	/* ---------- TODO (START) ---------- */
	t_ast_node	ast;
	t_ast_node	*ast_ptr = &ast;
	printf("==========> LAUNCHING AST BUILD <==========");
	builder_get_ast(&ast_ptr);
	printf("==========> AST BUILD DONE <==========");
	// TODO: runner_run(t_shell *shell);
	/* ---------- TODO (END) ---------- */
	print_warn("Runner not implemented yet => skipping execution loop\n");
	print_stop();
	shell_exit(err);
	return (error(ERR_NO));
}
