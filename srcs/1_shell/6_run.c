#include "shell_priv.h"
#include <stdlib.h>
# include "logs.h"	// DEBUG

t_error	shell_run(int argc, char **argv, char **envp)
{
	static const char	message[] = ": unable to malloc shell data struct: ";
	t_shell				*shell;
	t_error				err;
	t_error				history_err;

	print_start(99, "shell_run()");
	shell = malloc(sizeof(*shell));
	if (!shell)
		return (error_print(error_sys(), message, NULL, NULL));
	print_title("shell_init()");
	shell_init(shell);
	print_result("shell_init()");
	shell_set(shell);
	err = shell_load(shell, argc, argv, envp);
	if (err.type != ERR_NO)
		return(err);
	err = shell_exec_env();
	if (err.type != ERR_NO)
		return (err);
	err = runner_run(&shell->runner);
	history_err = history_save();
	if (history_err.type)
		(void)error_print(history_err, "history", NULL, NULL);
	return (err);
}
