#include "shell_priv.h"
#include "sig.h"
# include "logs.h"	// DEBUG

t_error	shell_load(t_shell *shell, int argc, char **argv, char **envp)
{
	t_error	err;

	print_title("shell_load()");
	err = env_load(&shell->params, argc, argv, envp);
	if (err.type == ERR_NO)
		err = sig_load();
	if (err.type == ERR_NO)
		err = history_load(&shell->history);
	if (err.type == ERR_NO)
		print_result("shell_load()");
	return (err);
}
