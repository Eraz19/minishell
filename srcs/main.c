#include "shell.h"
# include <locale.h>	// DEBUG
# include "logs.h"		// DEBUG
# include <assert.h>	// DEBUG

extern char	**environ;

int	main(int argc, char **argv)
{
	t_error	err;

	assert(argc > 0);
	assert(argv != NULL);
	assert(environ != NULL);
	setlocale(LC_NUMERIC, "de_DE");	// DEBUG
	shell_run(argc, argv, environ);
#ifdef DEBUG_LOGS
	print_stop();
#endif
	setlocale(LC_NUMERIC, "");	// DEBUG
	return ((int)err.type);
}
