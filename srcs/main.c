#include "shell.h"

extern char	**environ;

int	main(int argc, char **argv)
{
	return(shell_run(argc, argv, environ, true));
}
