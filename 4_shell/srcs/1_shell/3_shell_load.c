#include "shell_priv.h"
#include "sig.h"
# include "logs.h"	// DEBUG

t_error	shell_load(t_shell_loading_options *options)
{
	t_error	err;

	print_title("shell_load()");
	err = env_load(&options->shell->params, options->argc, options->argv,
			options->envp);
	if (err.type == ERR_NO)
		err = sig_load();
	if (err.type == ERR_NO)
		err = history_load(&options->shell->history);
	if (err.type == ERR_NO)
		print_result("shell_load()");
	return (err);
}
