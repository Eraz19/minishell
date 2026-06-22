#include "shell_priv.h"
#include <stdlib.h>
# include "logs.h"	// DEBUG

// @ret ERR_NO / ERR_LIBC.
static t_error	shell_exec_env(void)
{
	t_error	err;
	char	*raw_env;

	print_title("shell_exec_env()");
	if (!option_is_active(OPT_INTERACTIVE))
	{
		print_warn("non-interactive mode => skipping ENV execution\n");
		print_result("shell_exec_env()");
		return (error(ERR_NO));
	}
	err = params_get("ENV", &raw_env);
	if (err.type != ERR_NO && err.type != ERR_VAR_NOT_FOUND)
		return (error_print(error_sys(), "internal error", NULL, NULL));
	if (!raw_env)
	{
		print_warn("no ENV file to execute => skipping.\n");
		print_result("shell_exec_env()");
		return (error(ERR_NO));
	}
	if (option_is_active(OPT_STDIN_INPUT))
	{
		print_warn("Expander and Runner not implemented yet => skipping ENV execution\n");
		// TODO: expand ENV
		// TODO: exec ENV
	}
	else
		print_warn("OPT_STDIN_INPUT is not active => skipping ENV execution\n");
	print_result("shell_exec_env()");
	return (error(ERR_NO));
}

t_error	shell_start(int argc, char **argv, char **envp)
{
	static const char	message[] = ": unable to malloc shell data struct: ";
	t_shell				*shell;
	t_error				err;

	print_start(99, "shell_start()");
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
	err = shell_exec_env();
	if (err.type != ERR_NO)
		return (err);
	err = runner_loop(&shell->runner);
	shell_exit(err);
	return (error(ERR_NO));
}
