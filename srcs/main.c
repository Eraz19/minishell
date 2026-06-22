#include "shell.h"
# include <locale.h>	// DEBUG
# include "logs.h"		// DEBUG

int	main(int argc, char **argv, char **envp)
{
	t_error	shell_err;

	setlocale(LC_NUMERIC, "de_DE");	// DEBUG
	shell_err = shell_run(argc, argv, envp);
	shell_free();
	print_stop();
	setlocale(LC_NUMERIC, "");	// DEBUG
	return ((int)shell_err.type);
}
