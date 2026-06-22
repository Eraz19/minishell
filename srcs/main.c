#include "shell.h"
# include <locale.h>	// DEBUG

int	main(int argc, char **argv, char **envp)
{
	t_error	err;

	setlocale(LC_NUMERIC, "de_DE");	// DEBUG
	err = shell_start(argc, argv, envp);
	setlocale(LC_NUMERIC, "");	// DEBUG
	return ((int)err.type);
}
