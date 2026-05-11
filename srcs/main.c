#include "shell.h"
// #include "posix_helpers.h"
#include <unistd.h>

int	main(int argc, char **argv, char **envp)
{
	return ((int)shell_start(argc, argv, envp, NULL));
}
