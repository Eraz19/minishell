#include "shell_priv.h"
#include <stdlib.h>
# include "logs.h"	// DEBUG

void	shell_run(int argc, char **argv, char **envp)
{
	static const char	message[] = ": unable to malloc shell data struct: ";
	t_shell				*shell;
	t_error				err;
	t_error				history_err;

	print_start(99, "shell_run()");
	shell = malloc(sizeof(*shell));
	if (!shell)
	{
		error_print(error_sys(), message, NULL, NULL);
		return ;
	}
	print_title("shell_init()");
	shell_init(shell);
	print_result("shell_init()");
	shell_set(shell);
	err = shell_load(shell, argc, argv, envp);
	if (err.type != ERR_NO)
	{
		error_print(err, NULL, NULL);
		return ;
	}
	err = shell_exec_env();
	if (err.type != ERR_NO)
	{
		error_print(err, NULL, NULL);
		return ;
	}
	err = runner_run(&shell->runner);
	if (err.type)
		error_print(err, NULL, NULL);
	history_err = history_save();
	if (history_err.type)
		(void)error_print(history_err, "history", NULL, NULL);
	shell_free(shell);
}
