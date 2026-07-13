#include "shell.h"
# include "logs.h"	// DEBUG

t_error	shell_load(t_shell *shell, int argc, char **argv, char **envp)
{
	t_error	err;

	print_title("shell_load()");
	err = params_load(&shell->params, argc, argv, envp);
	if (err.type == ERR_NO)
		err = history_load(&shell->history);
	if (err.type == ERR_NO)
		err = scanner_load(&shell->scanner, shell->params.specials.source.data);
	if (err.type == ERR_NO)
		err = heredoc_load(&shell->heredoc);
	if (err.type == ERR_NO)
		err = builder_load(&shell->builder);
	if (err.type == ERR_NO)
		print_result("shell_load()");
	return (err);
}
