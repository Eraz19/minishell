#include "shell.h"
# include <locale.h>	// DEBUG
# include "logs.h"		// DEBUG

int	main(int argc, char **argv, char **envp)
{
	t_error	err;

	setlocale(LC_NUMERIC, "de_DE");	// DEBUG
	err = shell_run(argc, argv, envp);
	if (err.type)
		error_print(err, NULL, NULL);
	shell_free();
	print_stop();
	setlocale(LC_NUMERIC, "");	// DEBUG
	return ((int)err.type);
}
