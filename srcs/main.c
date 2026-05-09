#include "shell.h"

int	main(int argc, char **argv, char **envp)
{
	return ((int)shell_start(argc, argv, envp, NULL));
}
